// Copyright 2018 Theo Regis
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>  // std:: size_t
#include <stdexcept>  // C++ exceptions


namespace structures {

template<typename T>
/**
 * Classe lista de array
 */
class ArrayList {
 public:
    ArrayList() {
        max_size_ = DEFAULT_MAX;
        contents = new T[max_size_];
        end_ = max_size_;
    }
    /**
    * Construtor
    */        
    explicit ArrayList(std::size_t max_size) {
        max_size_ = max_size;
        contents = new T[max_size_];
        end_ = max_size_;
    }
    /**
    * Destrutor 
    */
    ~ArrayList() {
        delete []contents;
    }
    /**
    * Limpa a lista
    */
    void clear() {
        end_ = max_size_;
    }
    /**
    * Adiciona o elemento no final da lista
    */
    void push_back(const T& data) {
        if (full()) {
            throw std::out_of_range("Lista Cheia!");
        } else {
            if (empty()) {
                end_ = 0;
                contents[end_] = data;
            } else {
                end_++;
                contents[end_] = data;
            }
        }
    }
    /**
    * Adiciona o elemento no inicio da lista
    */
    void push_front(const T& data) {
        if (full()) {
            throw std::out_of_range("Lista Cheia!");
        } else {
            if (empty()) {
                end_ = 0;
                contents[0] = data;
            } else {
                for (std::size_t i = end_; i < max_size_; i--) {
                    contents[i+1] = contents[i];
                }
                end_++;
                contents[0] = data;
            }
        }
    }
    /**
    * Adiciona o elemento no indice especificado
    */
    void insert(const T& data, std::size_t index) {
        if (full()) {
            throw std::out_of_range("Lista Cheia!");
        } else {
            if (index > end_ || index == max_size_) {
                throw std::out_of_range("Posição Inválida");
            } else {
                if (empty()) {
                    contents[index] = data;
                    end_ = 0;
                } else {
                    for (std::size_t i = end_ + 1; i > index; i--) {
                        contents[i] = contents[i - 1];
                    }
                    end_++;
                    contents[index] = data;
                }
            }
        }
    }
    /**
    * Adiciona o elemento de acordo com a ordem
    */
    void insert_sorted(const T& data) {
        if (full()) {
            throw std::out_of_range("Lista Cheia!");
        } else {
            if (empty()) {
                insert(data, 0);
            } else {
                for (std::size_t i = 0; i <= end_; i++) {
                    if (contents[i] > data) {
                        insert(data, i);
                        return;
                    }
                }
                push_back(data);
            }
        }
    }
    /**
    * Remove o elemento do indice indicado
    */
    T pop(std::size_t index) {
        if (empty()) {
            throw std::out_of_range("Lista Vazia!");
        } else {
            if (index > end_) {
                throw std::out_of_range("Posição Inválida");
            } else {
                T data = contents[index];
                for (std::size_t i = index; i <= end_; i++) {
                    contents[i] = contents[i+1];
                }
                if (end_ == 0)
                    end_ = max_size_;
                else
                    end_--;
                return data;
            }
        }
    }
    /**
    * Remove o elemento do final da lista
    */
    T pop_back() {
        return pop(end_);
    }
    /**
    * Remove o elemento do inicio da lista
    */
    T pop_front() {
        return pop(0);
    }
    /**
    * Remove o primeiro dado que seja igual ao elemento especificado
    */
    void remove(const T& data) {
        std::size_t index = find(data);
        if (index != -1) {
            pop(index);
        }
    }
    /**
    * Checa se a lista está cheia
    */
    bool full() const {
        return end_ + 1 == max_size_;
    }
    /**
    * Checa se a lista esta vazia
    */
    bool empty() const {
        return end_ == max_size_;
    }
    /**
    * Checa se a lista contem um determinado dado
    */
    bool contains(const T&   data) const {
        std::size_t index = find(data);
        if (index == max_size_) {
            return false;
        } else {
            return true;
        }
    }
    /**
    * Encontra o indice de determinado data
    */
    std::size_t find(const T& data) const {
        if (empty()) {
            throw std::out_of_range("Lista Vazia");
        } else {
           std::size_t index = 0;
           while (index <= end_ && data != contents[index]) {
               index++;
           }
           if (contents[index] == data) {
               return (std::size_t) index;
           } else {
            return (std::size_t) max_size_;
           }
        }
    }
    /**
    * Retorna o tamanho atual da lista
    */
    std::size_t size() const {
        if (empty())
            return 0;
        else
            return end_ + 1;
    }
    /**
    * Retorna o tamanho máximo da lista
    */
    std::size_t max_size() const {
        return max_size_;
    }
    /**
    * Comment
    */
    T& at(std::size_t index) {
        if (index > end_) {
            throw std::out_of_range("Posição Inválida");
        } else {
            return contents[index];
        }
    }
    /**
    * Comment
    */
    T& operator[](std::size_t index) {
            return contents[index];
    }
    /**
    * Comment
    */
    const T& at(std::size_t index) const {
        if (index > end_) {
            throw std::out_of_range("Posição Inválida");
        } else {
            return contents[index];
        }
    }
    /**
    * Comment
    */
    const T& operator[](std::size_t index) const {
            return contents[index];
    }

 private:
    T* contents;
    std::size_t max_size_;
    std::size_t end_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures

#endif
