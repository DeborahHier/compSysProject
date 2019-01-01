#include "csapp.h"
#include "jsmn/jsmn.h" // https://github.com/zserge/jsmn
// using http://www.recipepuppy.com/about/api/

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

int main(void) {
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], arg3[MAXLINE], content[MAXLINE];
    char buffer[MAXLINE];
    char buffer2[MAXLINE];
    char json[MAXLINE];

    // Extract argument(s)
    if ((buf = getenv("QUERY_STRING")) != NULL) {
      p = strchr(buf, '&');
    	*p = '\0';
      strcpy(arg1, buf);
      strcpy(arg2, p+1);
      strcpy(arg2, p+2);

      // ----- add error handling for if there is only 1 arg -----
      // (i.e. if they just search for a recipe or 1 ingredient)
      // would they be null if they dont exist??

  //    if (arg2 != NULL) {

  //    }
  //    if (arg3 != NULL) {

  //    }
  //  }

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
    jsmn_parser parser;
    jsmontok_t t[100];  // We expect no more than 100 tokens
    static const char *JSON_STRING = json;

    jsmn_init(&parser);
  	r = jsmn_parse(&parser, json, strlen(json), t, sizeof(t)/sizeof(t[0]));
  	if (r < 0) {
  		printf("Failed to parse JSON: %d\n", r);
  		return 1;
  	}

    // Assume the top-level element is an object
    if (r < 1 || t[0].type != JSMN_OBJECT) {
      printf("Object expected\n");
      return 1;
    }

    // Loop over all keys of the root object
    char txt[MAXLINE];
  	for (i = 1; i < r; i++) {
  		if (jsoneq(JSON_STRING, &t[i], "title") == 0) {
  			// use strndup() to fetch string value
        txt = strndup(JSON_STRING + t[i+1].start, t[i+1].end-t[i+1].start);
        // add to content
  			sprintf(content, "<h2> %.*s </h2>\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
  			i++;

  // -*-*-*-*--*-*-*-*--*-*-*-*--*-*-*-*--*-*-*-*--*-*-*-*--*-*-*-*--*-*-*-*--*-*-*-*--*-*-*-*-
      } else if (jsoneq(JSON_STRING, &t[i], "href") == 0) {
  			txt = strndup(JSON_STRING + t[i+1].start, t[i+1].end-t[i+1].start);
        sprintf(content, "<a href=\"%.*s\"/>\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
        // sprintf(content, "<a href=\"%s\"/>\n", text);
  			i++;

  		} else if (jsoneq(JSON_STRING, &t[i], "thumbnail") == 0) {
  			/* We may want to do strtol() here to get numeric value */
        txt = strndup(JSON_STRING + t[i+1].start, t[i+1].end-t[i+1].start);
  			sprintf(content, "<img src=\"%.*s\" alt=\"alt thumbnail\"/>\n", t[i+1].end-t[i+1].start,
  					JSON_STRING + t[i+1].start);
  			i++;
  		} else if (jsoneq(JSON_STRING, &t[i], "ingredients") == 0) {
        txt = strndup(JSON_STRING + t[i+1].start, t[i+1].end-t[i+1].start);
        txt = strtok(txt, ",");  // split up at commas
        while (txt != NULL) {
          sprintf(content, "<li> %.*s </li>\n", t[i+1].end-t[i+1].start, JSON_STRING + t[i+1].start);
        }
        i++;

  		//	for (j = 0; j < t[i+1].size; j++) {
  		//		jsmntok_t *g = &t[i+j+2];
  		//		printf("  * %.*s\n", g->end - g->start, JSON_STRING + g->start);
  		//	}
  		//	i += t[i+1].size + 1;
  	//	} else {
  	//		printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
  	//				JSON_STRING + t[i].start);
  		//}
  	}
  }
  	return EXIT_SUCCESS;




    sprintf(content, "%s%s\n", content, json);   // store content and parsed data

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
