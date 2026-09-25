package com.mateusregasi.dto;

import java.math.BigDecimal;

public record ProdutoSemCategoriaResumo(Long id, String nome, BigDecimal preco, CategoriaResumo categoriaResumo) {
    
}
