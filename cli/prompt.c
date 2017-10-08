/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 19:08:28 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/10/06 14:53:09 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void make_buffer(struct input_line *buf) {
    buf->ln = malloc(PROMPT_SIZE_MAX+1);
	bzero(buf->ln, PROMPT_SIZE_MAX+1);
    buf->length = 0;
    buf->capacity = PROMPT_SIZE_MAX;
    buf->cursor = 0;
    buf->last_rendered = 0;
}

void destroy_buffer(struct input_line *buf) {
    free(buf->ln);
    make_buffer(buf);
}

void render_line(struct input_line *buf, WINDOW *win)
{
    int i = 0;

    while(i < buf->length)
    {
        chtype c = buf->ln[i];
        if(i == buf->cursor)
        {
            c |= A_REVERSE;
        }
        waddch(win,c);
        i++;
    }
    if(buf->cursor == buf->length)
    {
        waddch(win,' ' | A_REVERSE);
        i++;
    }
    int rendered = i;
    while(i < buf->last_rendered)
    {
        waddch(win,' ');
        i++;
    }
    buf->last_rendered = rendered;
}

int retrieve_content(struct input_line *buf, char *target, int max_len)
{
    int len;

    if (buf->length < (max_len - 1))
        len = buf->length;
    else
        len = (max_len - 1);
    ft_memcpy(target, buf->ln, len);
    target[len] = '\0';
    buf->cursor = 0;
    buf->length = 0;
    return len + 1;
}

void add_char(struct input_line *buf, char ch) {
    if(buf->length == buf->capacity)
        return ;
    ft_memmove(
        &buf->ln[buf->cursor+1],
        &buf->ln[buf->cursor],
        buf->length - buf->cursor
    );
    buf->ln[buf->cursor] = ch;
    ++buf->cursor;
    ++buf->length;
}


int handle_input_key(struct input_line *buf, int key)
{
    if (key == KEY_HOME)
        buf->cursor = 0;
    if (key == KEY_END)
        buf->cursor = buf->length;
    if (key == '\t')
        add_char(buf, '\t');
    if (key == KEY_BACKSPACE || key == 127 || key == 8)
	{
        if (buf->cursor <= 0)
		{
            return (0);
		}
        else
        {
            buf->cursor--;
            key = KEY_DC;
        }
	}
    if (key == KEY_DC)
        if(buf->cursor < buf->length) {
            ft_memmove(
                &buf->ln[buf->cursor],
                &buf->ln[buf->cursor+1],
                buf->length - buf->cursor - 1
            );
            buf->length --;
        }
    return (0);
}

int handle_input(struct input_line *buf, char *target, int max_len, int key) {
	if (key == KEY_RESIZE)
		return (0);
    if(!(key & KEY_CODE_YES) && isprint(key)) {
        add_char(buf, key);
        return 0;
    }
    if (key == ERR)
        return (0);
    if (key == KEY_LEFT)
        if(buf->cursor > 0)
            buf->cursor --;
    if (key == KEY_RIGHT)
        if (buf->cursor < buf->length)
            buf->cursor ++;
    handle_input_key(buf, key);
    if (key == KEY_ENTER || key == '\r' || key == '\n')
        return retrieve_content(buf, target, max_len);
    return (0);
}

int get_line_non_blocking(struct input_line *buf, char *target, int max_len) {
    while(1) {
        int key = getch();
        if(key == ERR) {
            return 0;
        }
        int n = handle_input(buf, target, max_len, key);
        if(n) {
            return n;
        }
    }
}
