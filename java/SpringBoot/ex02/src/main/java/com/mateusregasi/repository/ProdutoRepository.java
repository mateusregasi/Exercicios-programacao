package com.mateusregasi.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import com.mateusregasi.model.Produto;

public interface ProdutoRepository extends JpaRepository<Produto, Long> {
    
    @Query("select p from Produto p left join fetch p.categoria order by p.id")
    List<Produto> recuperarProdutosComCategoria();
}
