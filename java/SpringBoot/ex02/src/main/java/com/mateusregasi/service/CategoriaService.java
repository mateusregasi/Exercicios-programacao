package com.mateusregasi.service;

import java.util.ArrayList;
import java.util.List;

import org.springframework.stereotype.Service;
import org.springframework.web.bind.annotation.PathVariable;

import com.mateusregasi.dto.CategoriaDto;
import com.mateusregasi.dto.ProdutoDto;
import com.mateusregasi.model.Categoria;
import com.mateusregasi.model.Produto;
import com.mateusregasi.repository.CategoriaRepository;

@Service
public class CategoriaService {
    
    @Autowired
    CategoriaRepository categoriaRepository;
    CategoriaMapper categoriaMapper;

    public CategoriaService(CategoriaRepository categoriaRepository){
        this.categoriaRepository = categoriaRepository;
    }

    public CategoriaDto recuperarCategoriaDtoComProdutoDto(@PathVariable("idCategoria") Long id){
        Categoria categoria = categoriaRepository.recuperarCategoriaPorIdComProdutos(id)
            .orElseTrhow(() -> new EntidadeNaoEncontradaException(
                "Categoria com id = " + id + "não encontrada"
            ));
        List<ProdutoDto> lista = new ArrayList<>();
        for(Produto produto : categoria.getProdutos()){
            lista.add(
                new ProdutoDto(
                    produto.getId(),
                    produto.getNome(),
                    produto.getPreco(),
                    null
                )
            );
        }
        return new CategoriaDto(categoria.getId(), categoria.getNome(), lista);
    }

    public CategoriaResumoComProdutos recuperarCategoriaResumoComProdutos(Long id){
        Categoria categoria = categoriaRepository.recuperarCategoriaPorIdComProdutos(id)
            .orElseTrhow(() -> new EntidadeNaoEncontradaException(
                "Categoria com id = " + id + "não encontrada"
            ));;
        return categoriaMapper.toCategoriaResumoComProdutos(categoria);
    }
}
