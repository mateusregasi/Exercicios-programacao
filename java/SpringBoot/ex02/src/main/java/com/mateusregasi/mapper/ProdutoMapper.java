package com.mateusregasi.mapping;

import java.util.List;

import com.mateusregasi.dto.ProdutoComCategoriaResumo;
import com.mateusregasi.model.Produto;

@Mapper(componentModel = "spring")
public interface ProdutoMapper {

    List<ProdutoComCategoriaResumo> toProdutosComCategoriaResumo(List<Produto> produtos);
    List<ProdutoSemCategoriaResumo> toProdutosSemCategoriaResumo(List<Produto> produtos);

    @Mapping(source = "categoria", target = "categoriaResumo")
    ProdutoComCategoriaResumo toProdutoComCategoriaResumo(Produto produto);
    ProdutoSemCategoriaResumo toProdutoSemCategoriaResumo(Produto produto);

}
