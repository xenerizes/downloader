#pragma once


struct Url {
    const char* path {nullptr};
    const char* hostname {nullptr};
    const char* filename {nullptr};
    int port {0};
};
