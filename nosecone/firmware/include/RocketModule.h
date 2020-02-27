#pragma once

#define FILE_ID     0x0001
#define RECORD_KEY  0x1111

namespace Rocket {
    class RocketModule {
    public:
        virtual void preWarmup() {};
        virtual bool warmup() { return true; };
        virtual void refresh() = 0;
        virtual void calibrate() {};
        virtual void shutdown() {};
    };
};