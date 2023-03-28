#ifndef TEST_HPP
#define TEST_HPP

#include "Context.hpp"
#include "ft_irc.hpp"
#include "reply.hpp"
#include "Colors.h"

void run_test_suite( void );
void test_user_registration( Context & context );
void test_admin_info( Context & context );
void test_summon_users( Context & context );
void test_simple_privmsg( Context & context );
void test_names( Context & context );
void test_join( Context & context );
void test_part( Context & context );

void create_new_user( Context & context, int socket );
void send_test_message( Context & context, User & sender, std::string command );
void print_users_status( Context & context );

#endif
