#include "shell.h"


/**
 * my_help - changes the current directory of the process
 * @inform: Used for  maintaining constant function prototype.
 *  Return: 0
 */
int my_help(info_t *inform)
{
        char **arg_array;

        arg_array = inform->argv;
        _puts("Function yet to be implemented \n");
        if (0)
                _puts(*arg_array);
        return (0);
}





/**
 * _myexit - exits the shell
 * @inform: Used in maintaining constant function prototype.
 *  Return: exits with status (0)
 */
int _myexit(info_t *inform)
{
        int exitcheck;

        if (inform->argv[1])
        {
                exitcheck = _erratoi(inform->argv[1]);
                if (exitcheck == -1)
                {
                        inform->status = 2;
                        print_error(inform, "Illegal number: ");
                        _eputs(inform->argv[1]);
                        _eputchar('\n');
                        return (1);
                }
                inform->err_num = _erratoi(inform->argv[1]);
                return (-2);
        }
        inform->err_num = -1;
        return (-2);
}




/**
 * _cd - changes the current directory of the process
 * @informat: Maintains constant function prototype.
 *  Return: Always 0
 */
 int _cd(info_t *informat)
 {
         char *s, *dir, buffer[1024];
         int chdir_ret;

         s = getcwd(buffer, 1024);
         if (!s)
                 _puts(" failure msg here<<\n");
         if (!informat->argv[1])
         {
                 dir = get_env(informat, "HOME=");
                 if (!dir)
                         chdir_ret =
                                 chdir((dir = get_env(informat, "PWD=")) ? dir : "/");
                 else
                         chdir_ret = chdir(dir);
         }
         else if (_strcmp(informat->argv[1], "-") == 0)
         {
                 if (!get_env(informat, "OLDPWD="))
                 {
                         _puts(s);
                         _putchar('\n');
                         return (1);
                 }
                 _puts(get_env(informat, "OLDPWD=")), _putchar('\n');
                 chdir_ret =
                         chdir((dir = get_env(informat, "OLDPWD=")) ? dir : "/");
         }
         else
                 chdir_ret = chdir(informat->argv[1]);
         if (chdir_ret == -1)
         {
                 print_error(informat, "can't cd to ");
                 _eputs(informat->argv[1]), _eputchar('\n');
         }
         else
         {
                 _setenv(informat, "OLDPWD", get_env(informat, "PWD="));
                 _setenv(informat, "PWD", getcwd(buffer, 1024));
         }
         return (0);
 }
