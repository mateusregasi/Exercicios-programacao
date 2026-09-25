package com.mateusregasi.dto;

import java.math.BigDecimal;

public record ProdutoDto (
    Long id, 
    String nome, 
    BigDecimal preco, 
    CategoriaDto categoria
) {
    
}
