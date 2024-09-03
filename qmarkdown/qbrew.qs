// assume that marked is already loaded.
// assume marked exists
// const _marked = require(marked);
'use strict';

const noteInline = {
    name : 'note',
    level : 'block',

    start(src) { return src.match(/^@\s/m)?.index; },

    tokenizer(src, tokens) {
        const rule = /^((?:@\s.*(?:\n|$))+)/;
        const match = rule.exec(src);

        if (match) {
            const token = {
                type : 'note',
                raw : match[0],
                text : match[0].replace(/^@\s*/gm, '').trim(),
                tokens : []
            };

            this.lexer.blockTokens(token.text, token.tokens);
            return token;
        }
    },

    renderer(token) {
        return `<aside class="note">${this.parser.parse(token.tokens)}\n</aside>`;
    }
};


const statsInline = {
    name : 'istat',
    level : 'block',

    start(src) { return src.match(/^\$\s/m)?.index; },

    tokenizer(src, tokens) {
        const rule = /^((?:\$\s.*(?:\n|$))+)/;
        const match = rule.exec(src);

        if (match) {
            const token = {
                type : 'istat',
                raw : match[0],
                text : match[0].replace(/^\$\s*/gm, '').trim(),
                tokens : []
            };

            this.lexer.blockTokens(token.text, token.tokens);
            return token;
        }
    },

    renderer(token) {
        return `<aside class="stats">${this.parser.parse(token.tokens)}\n</aside>`;
    }
};

const colonTable = {
    name : 'colonTable',
    level : 'block',

    start(src) { return src.match(/^:\|/m)?.index; },

    tokenizer(src, tokens) {
        const rule = /^((?::\|.*(?:\n|$))+)/;
        const match = rule.exec(src);

        if (match) {
            const lines = match[0].trim().split('\n');
            const header = lines.shift().replace(/^\:\|\s*/, '').replace(/\s*\|\s*$/, '').split(/\s*\|\s*/);
            const body = lines.map(line => line.replace(/^\:\|\s*/, '').replace(/\s*\|\s*$/, '').split(/\s*\|\s*/));

            const token = {
                type : 'colonTable',
                raw  : match[0],
                header,
                body,
            };

            return token;
        }
    },

    renderer(token) {
        let table = `<table class="abilities">\n<thead>\n<tr>\n`;

        table += token.header.map(text => `<th>${text.trim()}</th>`).join('') + `\n</tr>\n</thead>\n<tbody>\n`;

        table += token.body.map(row =>
                    `<tr>\n${row.map(text => `<td>${text.trim()}</td>`).join('')}\n</tr>`
                ).join('\n') + `\n</tbody>\n</table>\n`;

        return table;
    }
};

marked.use({extensions : [noteInline, statsInline, colonTable]});
