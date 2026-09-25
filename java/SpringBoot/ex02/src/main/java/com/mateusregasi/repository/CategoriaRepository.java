package com.mateusregasi.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;

import com.mateusregasi.model.Categoria;

public interface CategoriaRepository extends JpaRepository<Categoria, Long> {

    @Query("select c from Categoria c left join fetch c.produtos where c.id = :id")
    Option<Categoria> recuperarCategoriaPorIdComProdutos(@Param("id") Long id);
}
