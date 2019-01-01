#include "csapp.h"
#include "jsmn/jsmn.h" // https://github.com/zserge/jsmn
// using http://www.recipepuppy.com/about/api/

int main(void) {
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], arg3[MAXLINE], content[MAXLINE];
    char buffer[MAXLINE];
    char buffer2[MAXLINE];
    char json[MAXLINE];

    // Extract argument(s)
    if ((buf = getenv("QUERY_STRING")) != NULL) {
      //
      p = strchr(buf, '&');
    	*p = '\0';
      strcpy(arg1, buf);
      strcpy(arg2, p+1);
      strcpy(arg2, p+2);
      // ----- add error handling for if there is only 1 arg -----
      // (i.e. if they just search for a recipe or 1 ingredient)
      // would they be null if they dont exist??

      if (arg2 != NULL) {

      }
      if (arg3 != NULL) {

      }
    }

    rio_t rio;
    char *host, *port;
    host = "www.recipepuppy.com";
    port = "80";

    // establish connection with API
    int clientfd = open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);


    if (clientfd == -1) {   // if it couldn't establish connection
      printf("ERROR: connection could not be established.");
    }

    // if they search for a certain recipe
    char *recipe = "q";
    char *arg = strstr(arg1, recipe);
    if (arg) {
      sprintf(buffer, "GET http://www.recipepuppy.com/api/?%s\n", arg1);   // save to buffer
                                        // ------ does request need to say "?q=%s" or just "?%s" ? ------
    }
    // if they search for ingredients
            // ----- ADD CODE ------

    Rio_writen(clientfd, buffer, MAXLINE);        // send request
    Rio_readlineb(&rio, buffer2, MAXLINE);        // get response
    sprintf(json, "%s%s\n", buffer2);             // store response in json buffer
    Close(clientfd);                              // close connection

    // parse jSON
    

    sprint(content, "%s%s\n", content, json);   // store content and parsed data

    // Make response body
    sprintf(content, "Results for %s: ", arg1);
    sprintf(content, "%s\r\n<p>", content);
    sprintf(content, "%s\r\n<p>", content);
    sprintf(content, "%sThanks for visiting!\r\n", content);

    // Generate HTTP response
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);

    exit(0);
}
