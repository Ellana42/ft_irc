#include "test.hpp"
#include "Context.hpp"

#define SOCKET_A 1
#define SOCKET_B 2

void run_test_suite( void )
{
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl;
	std::cout << CYAN "\t TESTING FT_IRC" RESET << std::endl;
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl << std::endl;

	std::cout << CYAN "-- Creating context" RESET << std::endl;
	Context & context = *( new Context() );

	create_new_user( context, SOCKET_A );
	create_new_user( context, SOCKET_B );

	print_users_status( context );

	test_user_registration( context );
	test_admin_info( context );
	test_summon_users( context );
	test_simple_privmsg( context );
	test_names( context );
	test_join( context );
	test_names( context );
	test_part( context );
	test_names( context );
	test_quit( context );

	std::cout << CYAN "-- Deleting context" RESET << std::endl;
	delete ( &context );
}

void test_user_registration( Context & context )
{
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl;
	std::cout << CYAN "\t TESTING USER REGISTRATION" RESET << std::endl;
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl << std::endl;

	User & alice = context.get_user_by_socket( SOCKET_A );
	User & bob = context.get_user_by_socket( SOCKET_B );

	send_test_message( context, alice, "PRIVMSG bob hi\r\n" );
	send_test_message( context, alice, "JOIN #test\r\n" );
	send_test_message( context, alice, "PART #test\r\n" );
	send_test_message( context, alice, "USER a\r\n" );
	send_test_message( context, alice, "USER a a a a a\r\n" );
	send_test_message( context, alice, "USER 3a a a a\r\n" );
	send_test_message( context, alice, "USER a- a a a\r\n" );
	send_test_message( context, alice, "USER alice alice alice alice\r\n" );
	send_test_message( context, alice, "USER x x x x\r\n" );
	send_test_message( context, alice, "NICK 1alice\r\n" );
	send_test_message( context, alice, "NICK a-lice\r\n" );
	send_test_message( context, alice, "NICK aaaaaaaaaa\r\n" );
	send_test_message( context, alice, "NICK alice\r\n" );
	send_test_message( context, alice, "USER x x x x\r\n" );

	print_users_status( context );

	send_test_message( context, bob, "NICK alice\r\n" );
	send_test_message( context, bob, "NICK\r\n" );
	send_test_message( context, bob, "NICK x x x\r\n" );
	send_test_message( context, bob, "NICK bob\r\n" );
	send_test_message( context, bob, "USER bob bob bob bob\r\n" );

	print_users_status( context );
}

void test_admin_info( Context & context )
{
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl;
	std::cout << CYAN "\t TESTING ADMIN & INFO COMMANDS" RESET << std::endl;
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl << std::endl;

	User & alice = context.get_user_by_nick( "alice" );
	User & bob = context.get_user_by_nick( "bob" );

	send_test_message( context, alice, "ADMIN\r\n" );
	send_test_message( context, alice, "INFO\r\n" );
	send_test_message( context, bob, "INFO hello\r\n" );
	send_test_message( context, bob, "ADMIN hello\r\n" );
}

void test_summon_users( Context & context )
{
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl;
	std::cout << CYAN "\t TESTING SUMMON & USERS COMMANDS" RESET << std::endl;
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl << std::endl;

	User & alice = context.get_user_by_nick( "alice" );
	User & bob = context.get_user_by_nick( "bob" );

	send_test_message( context, alice, "SUMMON\r\n" );
	send_test_message( context, alice, "USERS\r\n" );
	send_test_message( context, bob, "SUMMON hello\r\n" );
	send_test_message( context, bob, "USERS hello\r\n" );
}

void test_simple_privmsg( Context & context )
{
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl;
	std::cout << CYAN "\t TESTING USER-TO-USER PRIVMSG" RESET << std::endl;
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl << std::endl;

	User & alice = context.get_user_by_nick( "alice" );
	User & bob = context.get_user_by_nick( "bob" );

	send_test_message( context, alice, "PRIVMSG bob hello\r\n" );
	send_test_message( context, bob, "PRIVMSG alice hi I'm bob\r\n" );
	send_test_message( context, bob, "PRIVMSG alice :hi I'm bob\r\n" );
	send_test_message( context, alice, "PRIVMSG bob\r\n" );
}

void test_names( Context & context )
{
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl;
	std::cout << CYAN "\t TESTING NAMES" RESET << std::endl;
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl << std::endl;

	User & alice = context.get_user_by_nick( "alice" );
	User & bob = context.get_user_by_nick( "bob" );

	send_test_message( context, alice, "NAMES\r\n" );
	send_test_message( context, bob, "NAMES\r\n" );
	send_test_message( context, bob, "NAMES #test\r\n" );
	send_test_message( context, alice, "NAMES #test,#hello\r\n" );
}

void test_join( Context & context )
{
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl;
	std::cout << CYAN "\t TESTING JOIN" RESET << std::endl;
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl << std::endl;

	User & alice = context.get_user_by_nick( "alice" );
	User & bob = context.get_user_by_nick( "bob" );

	send_test_message( context, alice, "JOIN #test\r\n" );
	send_test_message( context, bob, "JOIN\r\n" );
	send_test_message( context, bob, "JOIN #test,#hello\r\n" );
	send_test_message( context, alice, "JOIN #hello\r\n" );
}

void test_part( Context & context )
{
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl;
	std::cout << CYAN "\t TESTING PART" RESET << std::endl;
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl << std::endl;

	User & alice = context.get_user_by_nick( "alice" );
	User & bob = context.get_user_by_nick( "bob" );

	send_test_message( context, alice, "PART #test :bye\r\n" );
	send_test_message( context, bob, "PART\r\n" );
	send_test_message( context, bob, "PART #test,#hello\r\n" );
}

void test_quit( Context & context )
{
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl;
	std::cout << CYAN "\t TESTING QUIT" RESET << std::endl;
	std::cout << CYAN "-----------------------------------------------" RESET <<
	          std::endl << std::endl;

	User & alice = context.get_user_by_nick( "alice" );
	User & bob = context.get_user_by_nick( "bob" );

	send_test_message( context, alice, "JOIN #test,#hello\r\n" );
	send_test_message( context, bob, "JOIN #test,#hello\r\n" );
	send_test_message( context, alice, "QUIT bye bye\r\n" );
	send_test_message( context, alice, "QUIT :bye bye\r\n" );
	send_test_message( context, bob, "QUIT :see ya !\r\n" );

	create_new_user( context, SOCKET_A );
	create_new_user( context, SOCKET_B );
	print_users_status( context );

	User & nick = context.get_user_by_socket( SOCKET_A );
	User & rick = context.get_user_by_socket( SOCKET_B );

	send_test_message( context, nick, "NICK nick\r\n" );
	send_test_message( context, nick, "USER nick nick nick nick\r\n" );
	send_test_message( context, rick, "NICK rick\r\n" );
	send_test_message( context, rick, "USER rick rick rick rick\r\n" );

	send_test_message( context, nick, "JOIN #test,#hello\r\n" );
	send_test_message( context, rick, "JOIN #test,#hello\r\n" );
	send_test_message( context, nick, "QUIT\r\n" );
	send_test_message( context, rick, "QUIT\r\n" );
}

void create_new_user( Context & context, int socket )
{
	std::cout << CYAN "-- Creating unregistered user on socket [" << socket << "]"
	          RESET << std::endl;
	context.create_unregistered_user( socket );
}

void print_users_status( Context & context )
{
	std::cout << CYAN "-------------" RESET << std::endl;
	context.debug_print_unregistered_users();
	context.debug_print_registered_users();
	std::cout << CYAN "-------------" RESET << std::endl;
}

void send_test_message( Context & context, User & sender, std::string command )
{
	std::cout << CYAN "-- " << sender << " : " << command << RESET << std::endl;
	context.handle_message( sender, command );
	std::cout << std::endl;
}

