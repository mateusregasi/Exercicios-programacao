package com.mateusregasi.dto;

import java.util.List;

public record CategoriaResumoComProduto(Long id, String nome, @JsonProperty("produtos") List<ProdutoSemCategoriaResumo> produtoSemCategoriaResumos) {
    
}
