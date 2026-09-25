package com.mateusregasi.exception;

// Antes: Exception era pra exceções esperadas e RuntimeException para não esperadas
public class EntidadeNaoEncontradaException extends RuntimeException {
    public EntidadeNaoEncontradaException(String msg){
        super(msg);
    }
}
