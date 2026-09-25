package com.mateusregasi.dto;

import java.util.List;

public record CategoriaDto(
    Long id, 
    String nome, 
    List<ProdutoDto> produtos
) {
    
}
