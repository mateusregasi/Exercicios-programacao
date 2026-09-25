package com.mateusregasi.exception;

public record ErrorResponse(
    LocalDateTime localDateTime,
    int errorCode,
    String error,
    String metodo,
    String requestUri,
    Map<String, String> map,
    String message
) {
    
}
