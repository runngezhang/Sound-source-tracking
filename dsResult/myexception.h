/*
 * exeption for audio reader
 */

#pragma once


class audio_read_exception :public std::exception{
public:
    audio_read_exception(char *exc_type);
    void except_sol();
};
