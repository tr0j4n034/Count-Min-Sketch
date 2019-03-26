//
//  HashColumn.hpp
//  CountMin Sketch
//
//  Created by Mahmud on 3/25/19.
//  Copyright © 2019 Mahmud. All rights reserved.
//

#ifndef HashColumn_hpp
#define HashColumn_hpp

template <typename T>
class HashColumn {
    int size;
    std::vector<T> entries;
    
public:
    HashColumn();
    HashColumn(int __size);
    HashColumn(std::vector<T> __entries);
    HashColumn(int __size, std::vector<T> __entries);
    int getSize();
    std::vector<T> getEntries();
    int getValueAt(int position);
    void updateValueAt(int position, T newValue);
    void incrementValueAt(int position);
    int getMinimumNaive();
    ~HashColumn();
};


#endif /* HashColumn_hpp */
