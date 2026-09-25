package com.carloribeiro.apirestful.controller;

import com.carloribeiro.apirestful.dto.ProdutoDto;
import com.carloribeiro.apirestful.exception.EntidadeNaoEncontradaException;
import com.carloribeiro.apirestful.model.Produto;
import com.carloribeiro.apirestful.service.ProdutoService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@CrossOrigin("http://localhost:5173")
@RestController
@RequestMapping("produtos")
public class ProdutoController {

    @Autowired
    private ProdutoService produtoService;

    @GetMapping   // GET para http://localhost:8080/produtos
    public List<Produto> recuperarProdutos() {
        return produtoService.recuperarProdutos();
    }

    @GetMapping("resumo")   // GET para http://localhost:8080/produtos/resumo?comCategoria=true
    public List<ProdutoDto> recuperarProdutosDto(
        @RequestParam(name = "comCategoria", defaultValue = "false") boolean comCategoria) {
        return produtoService.recuperarProdutosDto(comCategoria);
    }

    @GetMapping("mapstruct")
    // GET para http://localhost:8080/produtos/mapstruct?comCategoria=true
    public List<?> recuperarProdutosDtoComOuSemCategoriaResumo(
        @RequestParam(name = "comCategoria", defaultValue = "false") boolean comCategoria) {
        if (comCategoria) {
            return produtoService.recuperarProdutosDtoComCategoriaResumo();
        } else {
            return produtoService.recuperarProdutosDtoSemCategoriaResumo();
        }
    }

    @PostMapping
    public Produto cadastrarProduto(@RequestBody Produto produto) {
        return produtoService.cadastrarProduto(produto);
    }

    @PutMapping
    public Produto alterarProduto(@RequestBody Produto produto) {
        return produtoService.alterarProduto(produto);
    }

    @GetMapping("{idProduto}")
    // GET para http://localhost:8080/produtos/1
    public ResponseEntity<?> recuperarUmProdutoPorId(@PathVariable("idProduto") Long id) {
        try {
            Produto produto = produtoService.recuperarUmProdutoPorId(id);
            return new ResponseEntity<>(produto, HttpStatus.OK);
        } catch(EntidadeNaoEncontradaException e) {
            return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);
        }
    }

    @DeleteMapping("{idProduto}")
    // DELETE para http://localhost:8080/produtos/1
    public void removerProdutoPorId(@PathVariable("idProduto") Long id) {
        produtoService.removerProdutoPorId(id);
    }
}
