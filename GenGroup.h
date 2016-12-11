


#ifndef GENGROUP_H
#define GENGROUP_H


#include <stdbool.h>
#include  "Epsilon.h"

//********      types and functions types
**
* A pointer to group number/member. 
*/
typedef void * GroupMemberP;
typedef const void * ConstGroupMemberP;



//**************************
// functions to implement.


/**
 * @brief return the result of add(f(n),g(n))
 *   function name:addFunctions  
 * @param add pointer to A function that gets 2 GroupMemberP objects and return a GroupMemberP that is the result of the an opreation  on them.
 * @param f pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param g pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param n A  GroupMemberP 
 * @param freeMember pointer to A function that get GroupMemberP and frees it from memory.
 * @return the result of add(f(n),g(n)).  In case of an error return NULL.
 */
/*ADD addFunctions SIGNATURE HERE*/



/**
 * @brief return the result of f(g(n))
 *   function name:composeFunctions
 * @param f pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param g pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param n A  GroupMemberP 
 * @param freeMember pointer to A function that get GroupMemberP and frees it from memory.
 * @return the result of f(g(n)).  In case of an error return NULL.
 */
/*ADD composeFunctions SIGNATURE HERE*/


/**
 * @brief check if the given arguments define a an Abelian Group 
 * you should follow the definition of Abelian group -  see https://en.wikipedia.org/wiki/Abelian_group.
 * if some arguments are NULL print the following error message to stderr : "Error : <argument_name> is NULL\n"
 *   
 * @param IdentityElement - The  identity element.
 * @param members A struct of GroupMemberP which contain ALL the group members (including IdentityElement).
 * @param membersLen The length of members.
 * @param oper pointer to A function that gets 2 GroupMemberP objects and return a GroupMemberP that is the result of the opreation  on them.
 * @param freeMember pointer to A function that get GroupMemberP and frees it from memory.
 * @param compare pointer to A function that gets 2 GroupMemberP objects and return int >0 iff the first is bigger; 
            <0 if the second is bigger; and 0 iff they are equal(i.e. the diffrents beetween the diffrent between them is <EPSILON).
 * @return true iff the pramters an Abelian Group group.  In case of an error return false.
 */
bool isAbelianGroup(/*CHANGE HERE*/  IdentityElement, /*CHANGE HERE*/  members[], int membersLen, /*CHANGE HERE*/ oper, /*CHANGE HERE*/ freeMember, /*CHANGE HERE*/ compare); 


#endif // GENGROUP_H

