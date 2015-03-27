//
// Created by 张林 on 3/26/15.
//

#include <string.h>
#include <stdio.h>

char *status_text(int status) {
    char * status_text;
    switch (status){
        case 200:
            status_text = "Ok";
            break;
        case 201:
            status_text = "Created";
            break;
        case 202:
            status_text = "Accepted";
            break;
        case 304:
            status_text = "Not Modified";
            break;
        case 301:
            status_text = "Moved Permanently";
            break;
        case 302:
            status_text = "Found";
            break;
        case 400:
            status_text = "Bad Request";
            break;
        case 401:
            status_text = "Unauthorized";
            break;
        case 403:
            status_text = "Forbidden";
            break;
        case 404:
            status_text = "Not Found";
            break;
        case 405:
            status_text = "Method Not Allowed";
            break;
        case 500:
            status_text = "Internal Server Error";
            break;
        case 501:
            status_text = "Not Implemented";
            break;
        case 505:
            status_text = "HTTP Version Not Supported";
            break;
        default:
            status_text = "Unknown";
    }
    return status_text;
}

char *file_type(char *filename) {
    char * type;
    if(strstr(filename, ".html")){
        type = "text/html";
    }else if (strstr(filename, ".gif")){
        type = "image/gif";
    }else if (strstr(filename, ".jpg")) {
        type = "image/jpeg";
    }else if (strstr(filename, ".js")){
        type = "applicatiion/javascript";
    }else {
        type = "text/plain";
    }
    return type;
}
