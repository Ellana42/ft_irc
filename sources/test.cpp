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
	test_simple_privmsg( context );

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
	send_test_message( context, alice, "USER alice alice alice alice\r\n" );
	send_test_message( context, alice, "USER x x x x\r\n" );
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

