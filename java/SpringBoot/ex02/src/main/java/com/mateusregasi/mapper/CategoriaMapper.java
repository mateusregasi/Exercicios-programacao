package com.mateusregasi.mapping;

import org.mapstruct.Mapper;
import org.mapstruct.MapperConfig;

@MapperConfig(componentModel = "spring", uses = ProdutoMapper.class)
public interface CategoriaMapper {
    CategoriaResumoComProdutos toCategoriaResumoComProdutos(Categoria categoria);

    @Mapping(source = "produtos", target = "produtosSemCategoriaResumo")
    ProdutoComCategoriaResumo toCategoriaComProdutoResumo(Produto produto);
    
}
