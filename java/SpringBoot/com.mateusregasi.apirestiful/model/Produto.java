package model;

import java.math.BigDecimal;
import java.time.LocalDate;

public class Produto {
    private Long id;
    private String imagem;
    private String nome;
    private String descricao;
    private boolean disponivel;
    private int qtdEstoque;
    private BigDecimal preco;
    private LocalDate dataCadastro;
    private String categoria;

    
}
