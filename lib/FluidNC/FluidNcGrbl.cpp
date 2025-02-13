#include "FluidNcGrbl.h"

FluidNcGrbl::FluidNcGrbl(HardwareSerial* serial) {
    _serial = serial;
    _reportLenght = 0;
}

MachineStatus* FluidNcGrbl::getMachineStatus() {
    return &_machineStatus;
}

void FluidNcGrbl::home() {
    sendLineCommand("$H");
}

void FluidNcGrbl::jog(JogAxis axis, float distance) {
    char* cAxis;
    char* feedrate;
  
    if (axis == JogAxis::X) {
        cAxis = "X";
        feedrate = "1000";
    } else if (axis == JogAxis::Y) {
        cAxis = "Y";
        feedrate = "1000";
    } else if (axis == JogAxis::Z) {
        cAxis = "Z";
        feedrate = "150";
    }

    memset(_gCodeCommandBuffer, '\0', sizeof(_gCodeCommandBuffer));
    strcat(_gCodeCommandBuffer, "$J=G91 G21 F");
    strcat(_gCodeCommandBuffer, feedrate);
    strcat(_gCodeCommandBuffer, " ");
    strcat(_gCodeCommandBuffer, cAxis);


    uint8_t distanceLength = 1;
    if (distance > 100) {
        distanceLength+=2;
    } else if (distance > 10) {
         distanceLength+=1;
    }

    dtostrf(distance, 0, 2, _gCodeCommandBuffer + strlen(_gCodeCommandBuffer));
    sendLineCommand(_gCodeCommandBuffer);
}

void FluidNcGrbl::zero() {
    sendLineCommand("G10 L20 P0 X0 Y0 Z0");
}

void FluidNcGrbl::requestSdCardContent() {
    _lastSdCardFileIndex = 0;
    memset(_machineStatus.sdFiles, 0, sizeof(_machineStatus.sdFiles));
    sendLineCommand("$SD/List");
}

void FluidNcGrbl::run(char* file) {
    char runCommand[60];
    strncpy(runCommand, "$SD/Run=", 8);
    strcat(runCommand, file);
    sendLineCommand(runCommand);
}

void FluidNcGrbl::sendCommand(GCodeCommand command) {
    _serial->write((byte) command);
    Serial.write((byte) command);
}

void FluidNcGrbl::sendLineCommand(const char* line) {
    char c;
    while ((c = *line++) != '\0') {
        _serial->write(c);
        Serial.write(c);
    }
    _serial->write('\n');
    Serial.write('\n');
}

bool FluidNcGrbl::split(char* input, char** next, char delim) {
    char* pos = strchr(input, delim);
    if (pos) {
        *pos  = '\0';
        *next = pos + 1;
        return true;
    }
    *next = input + strlen(input);
    return false;
}

uint8_t FluidNcGrbl::parse_axes(char* s, float* axes) {
    char*  next;
    size_t n_axis = 0;
    do {
        split(s, &next, ',');
        if (n_axis < MAX_N_AXIS) {
            axes[n_axis++] = atopos(s);
        }
        s = next;
    } while (*s);
    return n_axis;
}

float FluidNcGrbl::atopos(const char* s) {
    int32_t  numerator;
    uint32_t denominator;
    atofraction(s, &numerator, &denominator);
    return (float)numerator / denominator;
}

bool FluidNcGrbl::atofraction(const char* p, int32_t* pnumerator, uint32_t* pdenominator) {
    int32_t  numerator   = 0;
    uint32_t denominator = 1;
    bool     negate      = false;
    char     c;

    if (*p == '-') {
        ++p;
        negate = true;
    }

    while (isdigit((int)(c = *p++))) {
        numerator = numerator * 10 + (c - '0');
    }
    if (c == '.') {
        while (isdigit((int)(c = *p++))) {
            numerator = numerator * 10 + (c - '0');
            denominator *= 10;
        }
        if (c == '%') {
            denominator *= 100;
            c = *p++;
        }
    } else if (c == '/') {
        while (isdigit((int)(c = *p++))) {
            denominator = denominator * 10 + (c - '0');
        }
    } else if (c == '%') {
        denominator *= 100;
        c = *p++;
    }
    if (negate) {
        numerator = -numerator;
    }
    *pnumerator   = numerator;
    *pdenominator = denominator;

    return c == '\0';
}

void FluidNcGrbl::parseIntegers(char* s, uint32_t* nums, int maxnums) {
    char*  next;
    size_t i = 0;
    do {
        if (i >= maxnums) {
            return;
        }
        split(s, &next, ',');
        nums[i++] = atoi(s);

        s = next;
    } while (*s);
}

void FluidNcGrbl::parseStatusReport(char* message) {
// The report wrapper, already removed, is <...>
    // The body is, for example,
    //   Idle|MPos:151.000,149.000,-1.000|Pn:XP|FS:0,0|WCO:12.000,28.000,78.000
    // i.e. a sequence of field|field|field

    char* next;
    split(message, &next, '|');

    // Malformed report
    if (*next == '\0') {
        return;  
    }

    // Save machine status
    memset(_machineStatus.status, '\0', sizeof(_machineStatus.status));
    strncpy(_machineStatus.status, message, sizeof(_machineStatus.status) - 1);

    const char* filename     = "";

    // ... handle it
    while (*next) {
        message = next;
        split(message, &next, '|');

        // MPos:, WPos:, Bf:, Ln:, FS:, Pn:, WCO:, Ov:, A:, SD: (ISRs:, Heap:)
        char* value;
        split(message, &value, ':');

        // Machine position
        if (strcmp(message, "MPos") == 0) {
            parse_axes(value, _machineStatus.mcos);
            continue;
        }

        // Work position
        if (strcmp(message, "WPos") == 0) {
            parse_axes(value, _machineStatus.wcos);
            continue;
        }

        if (strcmp(message, "Bf") == 0) {
            // buf_avail,rx_avail
            continue;
        }

        if (strcmp(message, "Ln") == 0) {
            //linenum = atoi(value);
            continue;
        }

        if (strcmp(message, "FS") == 0) {
            // feedrate [0], spindle_speed [1]
            parseIntegers(value, _machineStatus.feedRateAndSpindleSpeed, 2);  
            continue;
        }

        if (strcmp(message, "WCO") == 0) {
            // x,y,z,...
            // We do not use the WCO values because the DROs show whichever position is in the status report
            continue;
        }

        if (strcmp(message, "SD") == 0) {
            char* comma  = strchr(value, ',');
            if (comma) {
                *comma   = '\0';
                filename = comma + 1;
            }
            int32_t  numerator;
            uint32_t denominator;
            atofraction(value, &numerator, &denominator);
            _machineStatus.filePercent = numerator / denominator;
            memset(_machineStatus.filename, '\0', sizeof(_machineStatus.filename));
            strncpy(_machineStatus.filename, filename, sizeof(_machineStatus.filename) - 1);
            continue;
        }
    }
}

void FluidNcGrbl::parseSdCardReport(char* message) {
    char* next;
    split(message, &next, '|');

    // Malformed report
    if (*next == '\0') {
        return;  
    }
    
    memset(_machineStatus.sdFiles[_lastSdCardFileIndex].name, '\0', sizeof(_machineStatus.sdFiles[_lastSdCardFileIndex].name));
    strncpy(_machineStatus.sdFiles[_lastSdCardFileIndex].name, message, sizeof(_machineStatus.sdFiles[_lastSdCardFileIndex].name) - 1);

    while (*next) {
        message = next;
        split(message, &next, '|');

        char* value;
        split(message, &value, ':');

        if (strcmp(message, "SIZE") == 0) {
            _machineStatus.sdFiles[_lastSdCardFileIndex].size = atoi(value);
            continue;
        }
    }
    _lastSdCardFileIndex++;
}

bool FluidNcGrbl::isReportType(char* report, char** body, const char* prefix, const char* suffix) {
    size_t report_len = strlen(report);
    size_t prefix_len = strlen(prefix);

    if ((prefix_len <= report_len) && (strncmp(report, prefix, prefix_len) == 0)) {
        size_t suffix_len = strlen(suffix);
        if (suffix_len && (suffix_len < report_len) && (strcmp(report + report_len - suffix_len, suffix) == 0)) {
            report[report_len - suffix_len] = '\0';
        }
        *body = report + prefix_len;
        return true;
    }

    return false;
}

void FluidNcGrbl::parseReportMessage() {
    if (*_report == '\0') {
        return;
    }

    // ACK message for last sent command
    if (strcmp(_report, "ok") == 0) {
        return;
    }

    char* body;
    if (isReportType(_report, &body, "<", ">")) {
        parseStatusReport(body);
        return;
    }

    if (isReportType(_report, &body, "[FILE: ", "]")) {
        parseSdCardReport(body);
        return;
    }

    // if (is_report_type(_report, &body, "[GC:", "]")) {
    //     parse_gcode_report(body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[MSG:", "]")) {
    //     parse_msg(body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[JSON:", "]")) {
    //     handle_json(body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[VER:", "]")) {
    //     parse_version_report(body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "error:", "")) {
    //     _ackwait = false;
    //     parse_error(body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "ALARM:", "")) {
    //     parse_alarm(body);
    //     return;
    // }

    // if (is_report_type(_report, &body, "Grbl ", "")) {
    //     parse_signon(body);
    //     return;
    // }

    // if (is_report_type(_report, &body, "[PRB:", "]")) {
    //     parse_probe(body);
    //     return;
    // }

    // if (is_report_type(_report, &body, "[G54:", "]")) {
    //     parse_offset(G54,body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[G55:", "]")) {
    //     parse_offset(G55,body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[G56:", "]")) {
    //     parse_offset(G56,body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[G57:", "]")) {
    //     parse_offset(G57,body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[G58:", "]")) {
    //     parse_offset(G58,body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[G59:", "]")) {
    //     parse_offset(G59,body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[G28:", "]")) {
    //     parse_offset(G28,body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[G30:", "]")) {
    //     parse_offset(G30,body);
    //     return;
    // }
    // if (is_report_type(_report, &body, "[G92:", "]")) {
    //     parse_offset(G92,body);
    //     return;
    // }
}

void FluidNcGrbl::collectReport(uint8_t data) {
    if (data == '\r') {
        return;
    }

    if (data == '\n') {
        parseReportMessage();
        _report[0]  = '\0';
        _reportLenght = 0;
        return;
    }

    _report[_reportLenght++] = data;
    _report[_reportLenght] = '\0';
}

void FluidNcGrbl::poll() {
    uint8_t c;
    while (_serial->available()) {
        c = _serial->read();
        Serial.write(c);
        collectReport(c);
    }
}
