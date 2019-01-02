#include "csapp.h"
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

    if (clientfd == -1) {   // if it couldn't establish connection
      printf("ERROR: connection could not be established.");
    }

    char response[MAXLINE];
    Rio_writen(clientfd, buffer, MAXLINE);        // send the request to API
    Rio_readlineb(&rio, buffer2, MAXLINE);        // get response, store in buffer2
    Close(clientfd);                              // close the connection

    char *response_split;
    response_split = strchr(buffer2, '[');        // split response on 1st occurence of "{"
    *response_split = '\0';
    strcpy(response, response_split + 1);         // save necessary info in response

    // get top 3 search results for recipe
    // Extract recipe 1:
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
    char ingredients1_1[MAXLINE], ingredients1_2[MAXLINE], ingredients1_3[MAXLINE], r1_ingredients[MAXLINE];
    char *i1, *i2, *i3;
    strcpy(ingredients1_1, l2 + 1);
    i1 = strchr(ingredients1_1, ':');
    *i1 = '\0';
    strcpy(ingredients1_2, i1 + 1);
    i2 = strchr(ingredients1_2, '\"');
    *i2 = '\0';
    strcpy(ingredients1_3, i2 + 1);
    i3 = strchr(ingredients1_3, '\"');
    *i3 = '\0';
    strcpy(r1_ingredients, ingredients1_3);
    //      thumbnail
    char thumbnail1_1[MAXLINE], thumbnail1_2[MAXLINE], thumbnail[MAXLINE];
    char *th1, *th2;
    strcpy(thumbnail1_1, i3 +1);
    th1 = strchr(thumbnail1_1, ':');
    *th1 = '\0';
    strcpy(thumbnail1_2, th1 + 1);
    th2 = strchr(thumbnail1_2, '}');
    *th2 = '\0';
    strcpy(thumbnail, thumbnail1_2);

    // Extract recipe 2
    //      title
    char title2_1[MAXLINE], title2_2[MAXLINE], title2_3[MAXLINE], r2_title[MAXLINE];
    char *rt1, *rt2, *rt3;
    strcpy(title2_1, th2 + 1);
    rt1 = strchr(title2_1, ':');
    *rt1 = '\0';
    strcpy(title2_2, rt1 + 1);
    rt2 = strchr(title2_2, '\"');
    *rt2 = '\0';
    strcpy(title2_3, rt2 + 1);
    rt3 = strchr(title2_3, '\"');
    *rt3 = '\0';
    strcpy(r2_title, title2_3);
    //    href
    char link2_1[MAXLINE], link2_2[MAXLINE], r2_link[MAXLINE];
    char *lk1, *lk2;
    strcpy(link2_1, rt3 + 1);
    lk1 = strchr(link2_1, ':');
    *lk1 = '\0';
    strcpy(link2_2, lk1 + 1);
    lk2 = strchr(link2_2, ',');
    *lk2 = '\0';
    strcpy(r2_link, link2_2);
    //    ingredients
    char ingredients2_1[MAXLINE], ingredients2_2[MAXLINE], ingredients2_3[MAXLINE], r2_ingredients[MAXLINE];
    char *ri1, *ri2, *ri3;
    strcpy(ingredients2_1, lk2 + 1);
    ri1 = strchr(ingredients2_1, ':');
    *ri1 = '\0';
    strcpy(ingredients2_2, ri1 + 1);
    ri2 = strchr(ingredients2_2, '\"');
    *ri2 = '\0';
    strcpy(ingredients2_3, ri2 + 1);
    ri3 = strchr(ingredients2_3, '\"');
    *ri3 = '\0';
    strcpy(r2_ingredients, ingredients2_3);
    //    thumbnail
    char thumbnail2_1[MAXLINE], thumbnail2_2[MAXLINE], thumbnail2[MAXLINE];
    char *rth1, *rth2;
    strcpy(thumbnail2_1, ri3 +1);
    rth1 = strchr(thumbnail2_1, ':');
    *rth1 = '\0';
    strcpy(thumbnail2_2, rth1 + 1);
    rth2 = strchr(thumbnail2_2, '}');
    *rth2 = '\0';
    strcpy(thumbnail2, thumbnail2_2);

    // Extract recipe 3
    //      title
    char title3_1[MAXLINE], title3_2[MAXLINE], title3_3[MAXLINE], r3_title[MAXLINE];
    char *r3t1, *r3t2, *r3t3;
    strcpy(title3_1, rth2 + 1);
    r3t1 = strchr(title3_1, ':');
    *r3t1 = '\0';
    strcpy(title3_2, r3t1 + 1);
    r3t2 = strchr(title3_2, '\"');
    *r3t2 = '\0';
    strcpy(title3_3, r3t2 + 1);
    r3t3 = strchr(title3_3, '\"');
    *r3t3 = '\0';
    strcpy(r3_title, title3_3);
    //    href
    char link3_1[MAXLINE], link3_2[MAXLINE], r3_link[MAXLINE];
    char *lk3_1, *lk3_2;
    strcpy(link3_1, r3t3 + 1);
    lk3_1 = strchr(link3_1, ':');
    *lk3_1 = '\0';
    strcpy(link3_2, lk3_1 + 1);
    lk3_2 = strchr(link3_2, ',');
    *lk3_2 = '\0';
    strcpy(r3_link, link3_2);
    //    ingredients
    char ingredients3_1[MAXLINE], ingredients3_2[MAXLINE], ingredients3_3[MAXLINE], r3_ingredients[MAXLINE];
    char *r3i1, *r3i2, *r3i3;
    strcpy(ingredients3_1, lk3_2 + 1);
    r3i1 = strchr(ingredients3_1, ':');
    *r3i1 = '\0';
    strcpy(ingredients3_2, r3i1 + 1);
    r3i2 = strchr(ingredients3_2, '\"');
    *r3i2 = '\0';
    strcpy(ingredients3_3, r3i2 + 1);
    r3i3 = strchr(ingredients3_3, '\"');
    *r3i3 = '\0';
    strcpy(r3_ingredients, ingredients3_3);
    //    thumbnail
    char thumbnail3_1[MAXLINE], thumbnail3_2[MAXLINE], thumbnail3[MAXLINE];
    char *r3th1, *r3th2;
    strcpy(thumbnail3_1, r3i3 +1);
    r3th1 = strchr(thumbnail3_1, ':');
    *r3th1 = '\0';
    strcpy(thumbnail3_2, r3th1 + 1);
    r3th2 = strchr(thumbnail3_2, '}');
    *r3th2 = '\0';
    strcpy(thumbnail3, thumbnail3_2);

    // Make response body
    sprintf(content, "Recipe Results for \"%s:\"<p>\r\n", arg1);

    //    Recipe 1
    sprintf(content, "%s%s:<p>\r\n", content, r1_title);                                      // title
    sprintf(content, "%sIngredients: %s <p>\r\n", content, r1_ingredients);                   // ingredients
    sprintf(content, "%s<a href=%s> <img src=%s alt=\"recipe ingredients\"/></a>\r\n<p>",
            content, r1_link, thumbnail);                                                     // link and thumbnail

    //  Recipe 2
    sprintf(content, "%s%s:<p>\r\n", content, r2_title);                                      // title
    sprintf(content, "%sIngredients: %s <p>\r\n", content, r2_ingredients);                   // ingredients
    sprintf(content, "%s<a href=%s> <img src=%s alt=\"recipe ingredients\"/></a>\r\n<p>",
            content, r2_link, thumbnail2);                                                    // link and thumbnail

    // Recipe 3
    sprintf(content, "%s%s:<p>\r\n", content, r3_title);                                      // title
    sprintf(content, "%sIngredients: %s <p>\r\n", content, r3_ingredients);                   // ingredients
    sprintf(content, "%s<a href=%s> <img src=%s alt=\"recipe ingredients\"/></a>\r\n<p>",
            content, r3_link, thumbnail3);                                                    // link and thumbnail

    sprintf(content, "%sThanks for visiting!\r\n", content);
    // Generate HTTP response
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);

    exit(0);
}
