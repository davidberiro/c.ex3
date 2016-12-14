#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "GenGroup.h"


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
GroupMemberP addFunctions(GroupMemberP (*add)(GroupMemberP, GroupMemberP), GroupMemberP (*f)(GroupMemberP),\
                                GroupMemberP (*g)(GroupMemberP), GroupMemberP n, void (*freeMember)(GroupMemberP))
{
    GroupMemberP result = (*add)((*f)(n), (*g)(n));
    (*freeMember)(n);
    return result;
}



/**
 * @brief return the result of f(g(n))
 *   function name:composeFunctions
 * @param f pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param g pointer to A function that gets a GroupMemberP and return a GroupMemberP
 * @param n A  GroupMemberP
 * @param freeMember pointer to A function that get GroupMemberP and frees it from memory.
 * @return the result of f(g(n)).  In case of an error return NULL.
 */
GroupMemberP composeFunctions(GroupMemberP (*f)(GroupMemberP), GroupMemberP (*g)(GroupMemberP),\
                                    GroupMemberP n, void (*freeMember)(GroupMemberP))
{
	GroupMemberP result = (*f)((*g)(n));
	(*freeMember)(n);
	return result;
}

//returns 1 iff e*id=id=id*e
static int identityCheck(ConstGroupMemberP IdentityElement, GroupMemberP e, GroupMemberP (*oper)(GroupMemberP, GroupMemberP),
							void (*freeMember)(GroupMemberP), int (*compare)(GroupMemberP, GroupMemberP))
{	
	int retValue;
	GroupMemberP result1 = (*oper)(IdentityElement, e);
	GroupMemberP result2 = (*oper)(e, IdentityElement);
	if (((*compare)(result1, e)) ||  ((*compare)(result2, e)))
	{
		retValue = 0;
	}
	else
	{
		retValue = 1;
	}
	(*freeMember)(result1);
	(*freeMember)(result2);
	return retValue
}

static int associativeCheck(GroupMemberP e1, GroupMemberP e2, GroupMemberP e3, GroupMemberP (*oper)(GroupMemberP, GroupMemberP),
								void (*freeMember)(GroupMemberP), int (*compare)(GroupMemberP, GroupMemberP))
{
	int retValue = 1;
	GroupMemberP onetwo = (*oper)(e1, e2);
	GroupMemberP twothree = (*oper)(e2, e3);
	GroupMemberP result1 = (*oper)(onetwo, e3);
	GroupMemberP result2 = (*oper)(e1, twothree);
	if ((*compare)(result1, result2))
	{
		retValue = 0;
	}
	(*freeMember)(onetwo);
	(*freeMember)(twothree);
	(*freeMember)(result1);
	(*freeMember)(result2);
	return retValue;
}

static int closureCheck(GroupMemberP e1, GroupMemberP e2, GroupMemberP (*oper)(GroupMemberP, GroupMemberP),
								void (*freeMember)(GroupMemberP), int (*compare)(GroupMemberP, GroupMemberP)
								,GroupMemberP members[], int membersLen)
{
	int retValue = 0;
	GroupMemberP product = (*oper)(e1, e2);
	for (int i = 0; i < membersLen; i++)
	{
		if (!(*oper)(product, members[i]))
		{
			retValue = 1;
		}
	}
	(*freeMember)(product);
	return retValue;
}

//returns 1 iff e1*e2=e2*e1
static int commutativeCheck(GroupMemberP e1, GroupMemberP e2, GroupMemberP (*oper)(GroupMemberP, GroupMemberP),
								void (*freeMember)(GroupMemberP), int (*compare)(GroupMemberP, GroupMemberP))
{
	int retValue = 1;
	GroupMemberP result1 = (*oper)(e1, e2);
	GroupMemberP result2 = (*oper)(e2, e1);
	if ((*compare)(result1, result2)
	{
		retValue = 0;
	}
	(*freeMember)(result1);
	(*freeMember)(result2);
	return retValue;
}

//returns 1 iff e1 has an inverse
static int inverseCheck(ConstGroupMemberP IdentityElement, GroupMemberP e1, GroupMemberP (*oper)(GroupMemberP, GroupMemberP),
								void (*freeMember)(GroupMemberP), int (*compare)(GroupMemberP, GroupMemberP)
								,GroupMemberP members[], int membersLen)
{
	for (int i = 0; i < membersLen; i++)
	{
		GroupMemberP result = (*oper)(e1, members[i]);
		if (!(*compare)(result, IdentityElement))
		{
			(*freeMember)(result);
			return 1;
		}
		(*freeMember)(result);
	}
	return 0;
}




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
bool isAbelianGroup(ConstGroupMemberP IdentityElement, GroupMemberP members[], int membersLen, GroupMemberP (*oper)(GroupMemberP, GroupMemberP),
						 void (*freeMember)(GroupMemberP), int (*compare)(GroupMemberP, GroupMemberP)
{
	for (int i = 0; i < membersLen; i++)
	{
		if (!(inverseCheck(IdentityElement, members[i], oper, freeMember, compare, members, membersLen)))
		{
			printf("failed inverse property check\n");
			return false;
		}
		if (!(identityCheck(IdentityElement, members[i] ,oper, freeMember, compare)))
		{
			printf("failed identity property check\n");
			return false;
		}
		
		for (int j = 0; j < membersLen; j++)
		{
			if (!closureCheck(members[i], members[j], oper, freeMember, compare, members, membersLen))
			{
				printf("failed closure property check\n");
				return false;
			}
			if (!(commutativeCheck(members[i], members[j], oper, freeMember, compare)))
			{
				printf("failed commutative property check\n");
				return false;
			}

			for (int k = 0; k < membersLen; k++)
			{
				if (!(associativeCheck(members[i], members[j], members[k], oper, freeMember, compare)))
				{
					printf("failed associativeCheck\n");
					return false;
				}
			}
		}
	}
	return true;
}
