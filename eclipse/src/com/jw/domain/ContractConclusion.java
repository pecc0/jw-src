package com.jw.domain;
// Generated Oct 14, 2010 11:31:18 PM by Hibernate Tools 3.2.4.GA


import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.Table;

/**
 * ContractConclusion generated by hbm2java
 */
@Entity
@Table(name="contract_conclusion"
)
public class ContractConclusion  implements java.io.Serializable {


     private int id;
     private Contract contract;
     private Player player;

    public ContractConclusion() {
    }

    public ContractConclusion(int id, Contract contract, Player player) {
       this.id = id;
       this.contract = contract;
       this.player = player;
    }
   
     @Id 

    
    @Column(name="id", unique=true, nullable=false)
    public int getId() {
        return this.id;
    }
    
    public void setId(int id) {
        this.id = id;
    }

@ManyToOne(fetch=FetchType.LAZY)
    @JoinColumn(name="fk_contract", nullable=false)
    public Contract getContract() {
        return this.contract;
    }
    
    public void setContract(Contract contract) {
        this.contract = contract;
    }

@ManyToOne(fetch=FetchType.LAZY)
    @JoinColumn(name="fk_player", nullable=false)
    public Player getPlayer() {
        return this.player;
    }
    
    public void setPlayer(Player player) {
        this.player = player;
    }




}


