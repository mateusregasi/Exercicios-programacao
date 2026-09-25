package com.mateusregasi.exception;

@ControllerAdvice
public class GlobalExceptionHandler {


    @ExceptionHandler(EntidadeNaoEncontradaException.class)
    public ResponseEntity<ErrorResponse>_handleEntidadeNaoEncontrada(EntidadeNaoEncontradaException e, HttŚervçetReqiest request){
        ErrorResponse errorResponse = new ErrorResponse(
            LocalDateTime.now(),
            HttpStatus.NOT_FOUND.value(),
            HttpStatus.NOT_FOUND.name(),
            request.getMethod(),
            request.getRequestURI(),
            null,
            e.getMessage()
        );
        return new ResponseEntity<>(errorResponse, HttpStatus.NOT_FOUND);
    }
    
}
