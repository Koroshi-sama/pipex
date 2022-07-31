/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerrazik <aerrazik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 09:51:40 by aerrazik          #+#    #+#             */
/*   Updated: 2022/07/27 23:20:17 by aerrazik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include  <stdio.h> 
# include  <unistd.h>
# include <sys/wait.h>

 int  main ( void ) 
{ 
	pid_t pid ; 

	pid =  fork ( ) ; 
    printf("again %d\n", pid);
	if  ( pid ==  - 1 ) 
		return  ( 1 ) ; 
	else  if  ( ! pid ) 
	{ 
		printf ( "Child: I got a pid %d internally\n" , pid ) ; 
		printf ( "Child: Exiting with Code 0\n" ) ; 
	} 
	else  if  ( pid ) 
	{
		wait(NULL);
		printf ( "Parent: I have a Child which pid is %d\n" , pid ); 
		printf ( "Parent: Exiting with Code 0\n" );
	} 
	return  ( 0 ) ; 
}