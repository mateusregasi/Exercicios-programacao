package com.mateusregasi.apirestiful.controller;

import com.mateusregasi.apirestful.model.Produto;
import java.util.List;

@RestController
@RequestMapping("produtos")
public class ProdutoController{

    @Autowired(required=true)
    private ProdutoService ProdutoService;

    @GetMapping
    public List<Produto> recuperarProdutos(){
        return produtoService.recuperarProdutos();
    }

    @PostMapping
    public Produto cadastrarProduto(@RequestBody Produto produto){
        return produtoService.cadastrarProduto(produto);
    }
}