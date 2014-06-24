/**
 * @file nodeData.cpp
 * Purpose: implementation file for the NodeData class
 *
 * @author      James Murphree <murphs95@uw.edu>
 * @author      Vu Dinh <vdinh143@uw.edu>
 * @date        March 13 2014
 * @copyright   WTFPLv2.1
 */

#ifndef NODE_DATA_CPP
#define NODE_DATA_CPP

string const emptyToken = "hahaha";
int const emptyCount = -42;

/**
 * @brief Default constructor with default values 
 * 
 * @param someString string object to be stored as token inside the Node
 * @param   frequency integer value associated with the string, indicating
 *          the frequency of occurence for that string.
 */
NodeData::NodeData(string someString, int frequency)
                : token(someString), count(frequency) {}

/**
 * @brief Copy constructor
 * 
 * @param other original node to copy from
 */
NodeData::NodeData(const NodeData& other) {
    token = other.token;
    count = other.count;
}

/**
 * @brief Default destrutor
 * @details randomize data for security
 */
NodeData::~NodeData() {
    token = emptyToken;
    count = emptyCount;
}

NodeData& NodeData::operator = (const NodeData& other) {
    if (other != *this) {
        token = other.token;
        count = other.count;
    }
    return *this;
} 

// Comparision operators --------------------
/**
 * @brief overloaded equality comparison operator
 * @details compare for equality by token THEN by frequency
 * 
 * @param rightSide reference to the other NodeData object to compare against
 * @return `true` if the two NodeData have the exact same content, `false`
 *          otherwise
 */
bool NodeData::operator == (const NodeData& rightSide) const {
    return ((token == rightSide.token) && (count == rightSide.count));
}

/**
 * @brief overloaded equality comparison operator
 * @details compare for equality by token THEN by frequency
 * 
 * @param   rightSide reference to the other NodeData object to compare against
 * @return  `true` if the two NodeDatas do not have the exact same content,
 * `false` otherwise
 */
bool NodeData::operator != (const NodeData& rightSide) const {
    return !(*this == rightSide);
}

/**
 * @brief overloaded less-than comparison operator
 * @details Compare by token
 * 
 * @param   rightSide reference to the other NodeData object to compare against
 * @return  `true` if this token is less than the other token
 */
bool NodeData::operator < (const NodeData& rightSide) const {
    return token < rightSide.token;
}

/**
 * @brief overloaded greater-than comparison operator
 * @details Compare by token
 * 
 * @param rightSide reference to the other NodeData object to compare against
 * @return  `true` if this token is greater than the other token,
 *          `false` otherwise
 */   
bool NodeData::operator > (const NodeData& rightSide) const {
    return (*this != rightSide && !(*this < rightSide));
}

// Mutate and Get ---------------------------------

/**
 * @brief increment the frequency inside the NodeData
 */
void NodeData::increaseCount() {count++;}
/**
 * @brief decrement the frequency inside the NodeData
 */
void NodeData::decreaseCount() {count--;}

/**
 * @brief getter method to retrieve the frequency
 * @return integer value of frequency as stored in the NodeData
 */
int NodeData::getCount() const {return count;}

/**
 * @brief getter method to retrieve the token
 * @return string representation of the token as stored in the NodeData
 */
string NodeData::getToken() const {return token;}

/**
 * @brief overloaded output operator
 * @details append the content of the NodeData to the outstream
 * 
 * @param out ostream object to append content to
 * @param data NodeData object containing content to be appended
 */
ostream& operator << (ostream& out, const NodeData& data) {
    out << data.getToken() << "-" << data.getCount();
    return out;
}

#endif