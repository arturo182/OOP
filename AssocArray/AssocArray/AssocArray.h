#ifndef ASSOCARRAY_H
#define ASSOCARRAY_H

template<typename K, typename V>
class AssocArray
{
  public:
    AssocArray(int size): m_size(size)
    {
      m_keys = new K[size];
      m_values = new V[size];

      for(int i = 0; i < size; i++) {
        m_keys[i] = K();
	      m_values[i] = V();
      }
    }

    AssocArray(const AssocArray & other): m_size(other.m_size) 
    {
      m_keys = new K[m_size];
      m_values = new V[m_size];

      for(int i = 0; i < m_size; i++) {
        m_keys[i] = other.m_keys[i];
        m_values[i] = other.m_values[i];
      }
    }

    ~AssocArray()
    {
      delete [] m_keys;
	    delete [] m_values;
    }

    int znajdzIndeks(const K &key)
    {
      for(int i = 0; i < m_size; i++) {
        if(m_keys[i] == key) {
	        return i;
	      }
      }

      return -1;
    }

    V znajdzWartosc(const K &key)
    {
      int i = znajdzIndeks(key);

      return (i == -1) ? V() : m_values[i];
    }

    void dodajWartosc(const K &key, const V &value)
    {
      int i = znajdzIndeks(key);

      if(i > -1) {
        m_values[i] = value;
      } else {
        int j;

        for(j = 0; j < m_size; j++) {
          if(m_values[j] == V()) {
            m_keys[j] = key;
            m_values[j] = value;

            return;
          }
        }
       
        throw new exception("Tablica jest pelna.");
      }
    }

    void usunWartosc(const K &key)
    {
      int i = znajdzIndeks(key);

      if(i > -1) {
        m_keys[i] = K();
	      m_values[i] = V();
      } else {
        cout << "Nie znaleziono klucza \"" << key << "\"" << endl;
      }
    }

    int rozmiar()
    {
      return m_size;
    }

    void drukuj()
    {
      for(int i = 0; i < m_size; i++) {
        cout << "arr[\"" << m_keys[i] << "\"] = \"" << m_values[i] << "\";"  << endl;
      }
    }

    V &operator[](const K &key) 
    { 
      int i = znajdzIndeks(key);

      if(i == -1) {
        int j;

        for(j = 0; j < m_size; j++) {
          if(m_values[j] == V()) {
            m_keys[j] = key;
            i = j;
            
            return m_values[i];
          }
        }
       
        throw new exception("Tablica jest pelna.");
      }
      
      return m_values[i];
    }

    AssocArray<K, V> &operator=(const AssocArray<K, V> &other)
    {
      for(int i = 0; i < min(m_size, other.m_size); i++) {
        m_keys[i] = other.m_keys[i];
        m_values[i] = other.m_values[i];
      }

      if(m_size > other.m_size) {
        for(int i = other.m_size; i < m_size; i++) {
          m_keys[i] = K();
	        m_values[i] = V();
        }
      }

      return *this;
    }

  private:
    int m_size;
    V *m_values;
    K *m_keys;
};

#endif //ASSOCARRAY_H