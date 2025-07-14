FROM alpine:3.21

WORKDIR /srcs/requirements/nginx

RUN apk update && \
    apk add --no-cache nginx && \
    mkdir -p /run/nginx

COPY default.conf /etc/nginx/http.d/default.conf

CMD ["nginx", "-g", "daemon off;"]


