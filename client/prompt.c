/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/02 17:55:09 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void make_buffer(struct input_line *buf) {
    buf->ln = NULL;
    buf->length = 0;
    buf->capacity = 0;
    buf->cursor = 0;
    buf->last_rendered = 0;
}

void destroy_buffer(struct input_line *buf) {
    free(buf->ln);
    make_buffer(buf);
}

void render_line(struct input_line *buf, WINDOW *win) {
    int i = 0;
    for(; i < buf->length; i ++) {
        chtype c = buf->ln[i];
        if(i == buf->cursor) {
            c |= A_REVERSE;
        }
        waddch(win,c);
    }
    if(buf->cursor == buf->length) {
        waddch(win,' ' | A_REVERSE);
        i ++;
    }
    int rendered = i;
    // Erase previously rendered characters
    for(; i < buf->last_rendered; i ++) {
        waddch(win,' ');
    }
    buf->last_rendered = rendered;
}

int retrieve_content(struct input_line *buf, char *target, int max_len) {
    int len = buf->length < (max_len - 1) ? buf->length : (max_len - 1);
    memcpy(target, buf->ln, len);
    target[len] = '\0';
    buf->cursor = 0;
    buf->length = 0;
    return len + 1;
}

void add_char(struct input_line *buf, char ch) {
    // Ensure enough space for new character
    if(buf->length == buf->capacity) {
        int ncap = buf->capacity + 128;
        char *nln = (char*) realloc(buf->ln, ncap);
        if(!nln) {
            // Out of memory!
            return;
        }
        buf->ln = nln;
        buf->capacity = ncap;
    }

    // Add new character
    memmove(
        &buf->ln[buf->cursor+1],
        &buf->ln[buf->cursor],
        buf->length - buf->cursor
    );
    buf->ln[buf->cursor] = ch;
    ++ buf->cursor;
    ++ buf->length;
}

int handle_input(struct input_line *buf, char *target, int max_len, int key) {
    if(!(key & KEY_CODE_YES) && isprint(key)) {
        add_char(buf, key);
        return 0;
    }

    switch(key) {
    case ERR: /* no key pressed */ break;
    case KEY_LEFT:  if(buf->cursor > 0)           { buf->cursor --; } break;
    case KEY_RIGHT: if(buf->cursor < buf->length) { buf->cursor ++; } break;
    case KEY_HOME:  buf->cursor = 0;           break;
    case KEY_END:   buf->cursor = buf->length; break;
    case '\t':
        add_char(buf, '\t');
        break;
    case KEY_BACKSPACE:
    case 127:
    case 8:
        if(buf->cursor <= 0) {
            break;
        }
        buf->cursor --;
        // Fall-through
    case KEY_DC:
        if(buf->cursor < buf->length) {
            memmove(
                &buf->ln[buf->cursor],
                &buf->ln[buf->cursor+1],
                buf->length - buf->cursor - 1
            );
            buf->length --;
        }
        break;
    case KEY_ENTER:
    case '\r':
    case '\n':
        return retrieve_content(buf, target, max_len);
    }
    return 0;
}

int get_line_non_blocking(struct input_line *buf, char *target, int max_len) {
    while(1) {
        int key = getch();
        if(key == ERR) {
            // No more input
            return 0;
        }
        int n = handle_input(buf, target, max_len, key);
        if(n) {
            return n;
        }
    }
}
