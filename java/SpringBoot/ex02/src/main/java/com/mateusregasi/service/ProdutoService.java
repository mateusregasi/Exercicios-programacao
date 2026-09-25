package com.mateusregasi.service;

import com.mateusregasi.dto.CategoriaDto;
import com.mateusregasi.dto.ProdutoDto;
import com.mateusregasi.exception.EntidadeNaoEncontradaException;
import com.mateusregasi.model.Produto;

import com.mateusregasi.repository.ProdutoRepository;

import java.util.ArrayList;
import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;

@Service
public class ProdutoService {
    
    @Autowired
    private ProdutoRepository produtoRepository;
    private produtoWrapper produtoWrapper;
    
    public List<Produto> recuperarProdutos(){
        return produtoRepository.findAll();
    }

    public List<ProdutoDto> recuperarProdutosDto(boolean comCategoria){
        List<ProdutoDto> listaDeProdutosDto = new ArrayList<>();
        if(comCategoria){
            List<Produto> lista = produtoRepository.recuperarProdutosComCategoria();
            for(Produto produto : lista){
                listaDeProdutosDto.add(
                    new ProdutoDto(
                        produto.getId(),
                        produto.getNome(),
                        produto.getPreco(),
                        new CategoriaDto(
                            produto.getCategoria().getId(),
                            produto.getCategoria().getNome(),
                            null
                        )
                    )
                );
            }
        } else{
            List<Produto> lista = produtoRepository.findAll();
            for(Produto produto : lista){
                listaDeProdutosDto.add(
                    new ProdutoDto(
                        produto.getId(),
                        produto.getNome(),
                        produto.getPreco(),
                        null
                    )
                );
            }
        }
        return listaDeProdutosDto;
    }

    public Produto cadastrarProduto(Produto produto){
        return produtoRepository.save(produto);
    }

    public ResponseEntity<?> recuperarUmProdutoPorId(Long id){
        return produtoRepository.findById(id)
            .orElseThrow(() -> new EntidadeNaoEncontradaException(
                "Produto com id = " + id + " não encontrado"
            ));
    }

    public void removerProdutoPorId(Long id){
        produtoRepository.deleteById(id);
    }

    public List<ProdutoDtoComCategoria> recuperarProdutosDtoComCategoriaResumo(){
        List<Produto> produtos = produtoRepository.recuperarProdutosComCategoria();
        return produtoWrapper.toProdutosComCategoriaResumo(produtos);
    }

    public List<Produto> recuperarProdutosDtoSemCategoriaResumo(){
        List<Produto> produtos = produtoRepository.findAll();
        return produtoWrapper.toProdutosSemCategoriaResumo(produtos);
    }
}
