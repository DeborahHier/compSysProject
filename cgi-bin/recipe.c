#include "csapp.h"
// #include "ezxml/ezxml.c"
// #include "ezxml/ezxml.h"
// #include <stdio.h>
// #include "jsmn/jsmn.h"
// #include "jsmn/jsmn.c"


// using http://www.recipepuppy.com/about/api/

int main(void) {
    char *buf, *p;
    char search_val[MAXLINE], arg1[MAXLINE], content[MAXLINE];
    // arg2[MAXLINE], arg3[MAXLINE];
    char buffer[MAXLINE];
    char buffer2[MAXLINE];

    // Extract argument(s)
    if ((buf = getenv("QUERY_STRING")) != NULL) {
      p = strchr(buf, '=');
    	*p = '\0';
      strcpy(search_val, buf);
      // char *b = strchr(p + 1, "&");
      // *b = '\0';
      strcpy(arg1, p + 1);
      // strcpy(arg2, b + 1);
    }
    // ?format=xml&
    sprintf(buffer, "GET http://recipepuppy.com/api/?q=%s\n", arg1);   // save request to buffer

    // establish connection with API
    rio_t rio;
    char *host, *port;

    host = "www.recipepuppy.com";
    port = "80";
    int clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    // if (clientfd == -1) {   // if it couldn't establish connection
    //  printf("ERROR: connection could not be established.");
    //  fflush(stdout);
    //  exit(1);
    //}

    char response[MAXLINE];
    Rio_writen(clientfd, buffer, MAXLINE);        // send the request to API
    Rio_readlineb(&rio, buffer2, MAXLINE);        // get response, store in buffer2
    Close(clientfd);                              // close the connection

    char *response_split;
    response_split = strchr(buffer2, '[');       // split response on occurence of "{"
    *response_split = '\0';
    strcpy(response, response_split + 1);         // save necessary info in response

    // get top 3 search results for recipe

    // Recipe 1:
    //      title
    char recipe1[MAXLINE];
    char title1[MAXLINE], r1_title[MAXLINE];
    char *r1, *r2, *r3;
    r1 = strchr(response, ':');
    *r1 = '\0';
    strcpy(recipe1, r1 + 1);
    r2 = strchr(r1 + 1, '\"');
    *r2 = '\0';
    strcpy(title1, r2 + 1);
    r3 = strchr(title1, '\"');
    *r3 = '\0';
    strcpy(r1_title, title1);
    //      href
    char link1[MAXLINE], link1_2[MAXLINE], r1_link[MAXLINE];
    char *l1, *l2;
    strcpy(link1, r3 + 1);
    l1 = strchr(link1, ':');
    *l1 = '\0';
    strcpy(link1_2, l1 + 1);
    l2 = strchr(link1_2, ',');
    *l2 = '\0';
    strcpy(r1_link, link1_2);

    //      ingredients



    // r2 = strchr(r1 + 1, '}');
    // *r2 = '\0';
    // strcpy(recipe2, r1 + 1);
    // r3 = strchr(r2 + 1, '}');
    // *r3 = '\0';
    // strcpy(recipe3, r2 + 1);


    // char t1[MAXLINE], t2[MAXLINE], t3[MAXLINE];
    // sscanf(title, "%s %s %s", test, test3, test4);
    // char *title1_1 = t1;
    // char *title1_2 = t2;
    // char *title1_3 = t3;
    // sprintf(content, "<h2> %s %s %s  \r\n</h2>", title1_1, title1_2, title1_3);

  //  if (response[1] == 't' && response[2] == 'i' && response[3] == 't'      // if its a "title" field
    //  && response[4] == 'l' && response[5] == 'e')

      //   }



    // strcpy(test, response_split + 3);
    // sscanf(test, "%s", &test2);
    // sprintf(content, "%s %s\n", test);

    // sprintf(content, "%s%s\n", content, response);

    // parse XML
    // FILE *response;
    // response = fopen("response.xml", "w+");   // open response.xml in writing mode
    // if (response) {                           // if the file is opened successfully:
    //   fputs(xml, response);                   //    put the xml response from API in reponse file
    // }
    // fclose(response); // close file

    // response = fopen("response.xml", "r"); // open file for reading

    //if (response) {    // if opened successfully
    //  printf("File contents:\n");
    //  char ch;
    //  while ( (ch = fgetc(response)) != EOF ) {
    //    printf("%c", ch);
    //  }
    //} else {
    //  printf("Failed to open the file for reading\n");
    //}

    // ezxml_t recipes = ezxml_parse_file("response.xml");
    // sprintf(content, "<h1> %s </h1>\n", ezxml_get(recipes, "recipe", 2, "title", -1));
    // ezxml_free(recipes);

    // Make response body
    sprintf(content, "<h1> Recipe Results for \"%s:\"\r\n</h1>", arg1);
    sprintf(content, "<h2> %s\r\n</h2>", r1_title);
    sprintf(content, "<a href=\"%s\"/> Click here for the recipe!\r\n</a>", r1_link);
    // sprintf(content, "%s%s %s %s\r\n<p>", content, t, l, m);
    // sprintf(content, "%s %s\r\n<p>", content, test);
    // sprintf(content, "%s\r\n<p>", content);
    // sprintf(content, "%s\r\n<p>", content);
    sprintf(content, "%sThanks for visiting!\r\n", content);
    // Generate HTTP response
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);

    exit(0);
}
