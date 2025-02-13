#ifndef FLUID_NC_GRBL_h
#define FLUID_NC_GRBL_h

#include <Arduino.h>

#define REPORT_BUFFER_LEN 1024
#define SD_CARD_FILES_BUFFER_LEN 100

#define UART_TIMEOUT 2000
#define STATUS_REQUEST_FREQ 1000

#define MAX_N_AXIS 3
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

enum class GCodeCommand {
    STATUS_REPORT = 0x3F // '?'
};

enum class JogAxis {
  X,
  Y,
  Z
};

enum class GCodeLineCommand {
  HOME
};

struct SdCardFile {
  char name[50];
  uint32_t size;
};

struct MachineStatus {
    char status[10];
    float wcos[MAX_N_AXIS];
    float mcos[MAX_N_AXIS];
    uint32_t feedRateAndSpindleSpeed[2];
    char filename[50];
    uint32_t filePercent;
    SdCardFile sdFiles[SD_CARD_FILES_BUFFER_LEN];
};

class FluidNcGrbl {
    public:
        FluidNcGrbl(HardwareSerial* serial);
        void poll();
        void requestSdCardContent();
        void sendCommand(GCodeCommand command);
        void home();
        void jog(JogAxis axis, float distance);
        void zero();
        void run(char* file);
        MachineStatus* getMachineStatus();
    private:
        HardwareSerial* _serial;
        MachineStatus _machineStatus;
        uint16_t _reportLenght;
        uint16_t _lastSdCardFileIndex;
        char _report[REPORT_BUFFER_LEN];
        uint32_t _lastStatusRequest;
        char _gCodeCommandBuffer[50];

        void sendLineCommand(const char* line);
        bool split(char* input, char** next, char delim);
        void collectReport(uint8_t data);
        void parseReportMessage();
        bool isReportType(char* report, char** body, const char* prefix, const char* suffix);
        void parseStatusReport(char* message);
        void parseSdCardReport(char* message);
        uint8_t parse_axes(char* s, float* axes);

        float atopos(const char* s);
        bool atofraction(const char* p, int32_t* pnumerator, uint32_t* pdenominator);
        void parseIntegers(char* s, uint32_t* nums, int maxnums);
};

#endif