#pragma once


#define SINGLE(type) static type* GetInst() { static type manager; return &manager; }