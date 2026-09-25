package com.mateusregasi.dto;

import java.math.BigDecimal;

import com.fasterxml.jackson.annotation.JsonProperty;

public record ProdutoComCategoriaResumo(Long id, String nome, BigDecimal preco, @JsonProperty("categoria") CategoriaResumo categoriaResumo) {
    
}
