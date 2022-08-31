#include <Core/MappedFile.h>
#include <JR/Defer.h>
#include <JR/Keywords.h>
#include <JR/SingleSplit.h>
#include <JR/Try.h>
#include <Main/Main.h>
#include <stdio.h>
#include <stdlib.h>

[[noreturn]] static void usage(int exit_code = 0);

static ErrorOr<void> parse_embed(StringView embed);
static StringView skip_whitespace(StringView value);

ErrorOr<int> Main::main(int argc, c_string argv[])
{
    if (argc < 2)
        usage(1);
    let filename = argv[1];
    var file = TRY(Core::MappedFile::open(filename));
    Defer close_file = [&] {
        file.close();
    };

    while (!file.eof()) {
        let original_line = *file.read_line();
        let line = skip_whitespace(original_line);
        if (line.starts_with("#pragma embed")) {
            let[_, embed] = TRY(line.split_on_first(' '));
            TRY(parse_embed(embed));
        } else {
            printf("%.*s\n",
                original_line.size(),
                original_line.data());
        }
    }

    return 0;
}

static bool is_whitespace(char character)
{
    return character == ' ' || character == '\t';
}

static StringView skip_whitespace(StringView value)
{
    while (is_whitespace(value[0])) {
        value = value.split_view(1, value.size());
    }
    return value;
}

StringView remove_quotes(StringView value, StringView quote)
{
    var start = 0;
    if (value.starts_with(quote))
        start = quote.size();
    var end = value.size();
    if (value.ends_with(quote))
        end = end - quote.size();
    return value.split_view(start, end);
}

static ErrorOr<void> parse_embed(StringView embed)
{
    let[_, quoted_filename] = TRY(embed.split_on_first(' '));

    StringView quote = "\"";
    if (!quoted_filename.starts_with(quote))
        return Error::from_string_literal("Missing start quote");
    if (!quoted_filename.ends_with(quote))
        return Error::from_string_literal("Missing end quote");

    let filename = remove_quotes(quoted_filename, "\"");

    let file = TRY(Core::MappedFile::open(filename));
    Defer close_file = [&] {
        file.close();
    };

    let file_view = file.view();
    printf("    ");
    for (u32 i = 0; i < file_view.size(); i++) {
        if ((i + 1) % 8 == 0)
            printf("\n    ");
        printf("%u, ", file_view[i]);
    }
    printf("\n");

    return {};
}

[[noreturn]] static void usage(int exit_code)
{
    var out = exit_code ? stderr : stdout;
    fprintf(out, "USAGE: %s file\n", Main::program_name());
    exit(exit_code);
}
