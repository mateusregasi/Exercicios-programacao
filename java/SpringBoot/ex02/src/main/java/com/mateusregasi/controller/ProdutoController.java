package com.mateusregasi.controller;

import com.mateusregasi.dto.ProdutoDto;
import com.mateusregasi.model.Produto;
import com.mateusregasi.service.ProdutoService;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("produtos")
public class ProdutoController{

    @Autowired(required=true)
    private ProdutoService produtoService;

    @GetMapping
    public List<Produto> recuperarProdutos(){
        return produtoService.recuperarProdutos();
    }

    // GET: http://localhost:8080/produtos/resumo?comCategoria=true
    @GetMapping("resumo")
    public List<ProdutoDto> recuperarProdutosDto(
        @RequestParam(name = "comCategoria", defaultValue = "false") boolean comCategoria
    ){
        return produtoService.recuperarProdutosDto(comCategoria);
    }

    @GetMapping("{idProduto}")
    public ResponseEntity<?> recuperarUmProdutoPorId(@PathVariable("idProduto") Long id){
        try{
            Produto produto = produtoService.recuperarUmProdutoPorId(id);
            return new ResponseEntity<>(produto, HttpStatus.OK);
        } catch(EntidadeNaoEncontradaException e){
            return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);

        }
    }

    @PostMapping
    public Produto cadastrarProduto(@RequestBody Produto produto){
        return produtoService.cadastrarProduto(produto);
    }

    @DeleteMapping("{idProduto}")
    public ResponseEntity<?> removerProdutoPorId(@PathVariable("idProduto") Long id){
        produtoService.removerProdutoPorId(id);
        return null;
    }

    @GetMapping("mapstruct")
    public List<?> recuperarProdutosDtoComOuSemCategoriaResumo(
        @RequestParam(name = "comCategoria", defaultValue = "false") boolean comCategoria
    ){
        if(comCategoria){
            return produtoService.recuperarProdutosDtoComCategoriaResumo();
        } else{
            return produtoService.recuperarProdutosDtoSemCategoriaResumo();
        }
        return produtoService.recuperarProdutosDto(comCategoria);
    }

}