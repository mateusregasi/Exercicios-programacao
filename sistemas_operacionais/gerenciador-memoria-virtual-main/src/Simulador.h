﻿//
// Created by Nathan Pinheiro on 05/06/2025.
//
#pragma once

#ifndef SIMULADOR_H
#define SIMULADOR_H

typedef struct TLB TLB;

#include <stdint.h>
#include "nalloc.h"
#include "ProcessHashMap.h"
#include "ProcessQueue.h"




typedef enum {
    SUB_POLICY_LRU,
    SUB_POLICY_CLOCK,
    SUB_POLICY_RANDOM,
} SubPolicyType;

typedef struct {
    uint32_t PAGE_SIZE;
    uint32_t MP_SIZE;
    uint32_t MS_SIZE;
    uint32_t TLB_SIZE;
    uint32_t TIME_SLICE;
    uint32_t BITS_LOGICAL_ADDRESS;
    SubPolicyType SUB_POLICY_TYPE;
} SimulationConfig;


typedef struct Simulador {
    SimulationConfig config;
    ProcessHashMap* process_map_main;
    ProcessHashMap* process_map_secondary;
    ProcessQueue* process_queue;

    Process* current_process;

    NallocContext main_memory_ctx;
    NallocContext secondary_memory_ctx;

    TLB* tlb;

    uint32_t current_cycle;
    bool important_cycle;
} Simulador;

extern Simulador* simulador;

// Funções do simulador
Simulador* create_simulator(const SimulationConfig config);
void destroy_simulator(Simulador* sim);
Process* get_process_by_pid(Simulador* simulador, uint32_t pid);
bool proxima_acao(Simulador* sim);
char* generate_simulator_json(Simulador* sim);



#endif //SIMULADOR_H
