package com.mateusregasi.apirestiful.service;

import com.mateusregasi.apirestiful.model.Produto;

import repository.ProdutoRepository;

import java.util.List;

@Service
public class ProdutoService {
    
    @Autowired
    private ProdutoRepository produtoRepository;
    
    public List<Produto> recuperarProdutos(){
        return produtoRepository.findAll();
    }

    public Produto cadastrarProduto(Produto produto){
        return produtoRepository.save(produto);
    }
}
