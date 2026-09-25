package com.mateusregasi.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.mateusregasi.dto.CategoriaDto;
import com.mateusregasi.service.CategoriaService;

import lombok.RequiredArgsConstructor;

@RequiredArgsConstructor
@RestController
@RequestMapping("categorias")
public class CategoriaController {
    
    private final CategoriaService categoriaService;

    @GetMapping("{idCategoria}")
    public CategoriaDto recuperarCategoriaDtoComProdutoDto(@PathVariable("idCategoria") Long id){
        return categoriaService.recuperarCategoriaDtoComProdutoDto(id);
    }

    @GetMapping("mapstruct/{idCategoria}")
    public List<CategoriaResumoComProdutos> recuperarCategoriaResumoComProdutos(
        @PathVariable("idCategoria") Long id
    ){
        return categoriaService.recuperarCategoriasResumoDtoComProdutosDto(id);
    }
}
