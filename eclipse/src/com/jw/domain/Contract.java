package com.jw.domain;
// Generated Oct 14, 2010 11:31:18 PM by Hibernate Tools 3.2.4.GA


import java.util.HashSet;
import java.util.Set;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import javax.persistence.Table;

/**
 * Contract generated by hbm2java
 */
@Entity
@Table(name="contract"
)
public class Contract  implements java.io.Serializable {


     private int id;
     private ContractDesign contractDesign;
     private Player player;
     private String description;
     private Set contractConclusions = new HashSet(0);
     private Set contractProps = new HashSet(0);
     private Set tasks = new HashSet(0);

    public Contract() {
    }

	
    public Contract(int id, ContractDesign contractDesign, Player player, String description) {
        this.id = id;
        this.contractDesign = contractDesign;
        this.player = player;
        this.description = description;
    }
    public Contract(int id, ContractDesign contractDesign, Player player, String description, Set contractConclusions, Set contractProps, Set tasks) {
       this.id = id;
       this.contractDesign = contractDesign;
       this.player = player;
       this.description = description;
       this.contractConclusions = contractConclusions;
       this.contractProps = contractProps;
       this.tasks = tasks;
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
    @JoinColumn(name="fk_contract_design", nullable=false)
    public ContractDesign getContractDesign() {
        return this.contractDesign;
    }
    
    public void setContractDesign(ContractDesign contractDesign) {
        this.contractDesign = contractDesign;
    }

@ManyToOne(fetch=FetchType.LAZY)
    @JoinColumn(name="fk_creator", nullable=false)
    public Player getPlayer() {
        return this.player;
    }
    
    public void setPlayer(Player player) {
        this.player = player;
    }

    
    @Column(name="description", nullable=false, length=512)
    public String getDescription() {
        return this.description;
    }
    
    public void setDescription(String description) {
        this.description = description;
    }

@OneToMany(fetch=FetchType.LAZY, mappedBy="contract")
    public Set getContractConclusions() {
        return this.contractConclusions;
    }
    
    public void setContractConclusions(Set contractConclusions) {
        this.contractConclusions = contractConclusions;
    }

@OneToMany(fetch=FetchType.LAZY, mappedBy="contract")
    public Set getContractProps() {
        return this.contractProps;
    }
    
    public void setContractProps(Set contractProps) {
        this.contractProps = contractProps;
    }

@OneToMany(fetch=FetchType.LAZY, mappedBy="contract")
    public Set getTasks() {
        return this.tasks;
    }
    
    public void setTasks(Set tasks) {
        this.tasks = tasks;
    }




}


