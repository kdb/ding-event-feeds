Ding event feed specification
=============================

Ding event feeds are an extension of the [Atom syndication format][atom-sf]
as defined by [RFC 4287][].

At the very least, you will need to have read
[the format introduction][atom-sf] to understand this document.

## Elements of `<feed>` ##

The feed elements are as specified in [Atom][atom-sf].

## Elements of `<entry>` ##

### Atom entry attributes ###

A Ding event feed must use mentioned Atom fields in the specified way:

* `id`
  
    The `id` element must be your site’s base URL plus the system URL
    for the event in question. It must not use a path alias, since those
    might change over time.
    
    These is a valid example:

        <id>http://bibliotek.kk.dk/node/35</id>

    This is a required attribute.

* `title`
  
    This is the event title, which will be used as node title when the
    event is imported. As also specified by Atom, this must be a simple
    text string. No HTML/XML allowed.

    This is a required attribute.

* `updated`

    Just like the Atom format, updated must be a [RFC 3339][] compliant
    timestamp for when the content was last updated.

    This is a required attribute.

[atom-sf]: http://www.atomenabled.org/developers/syndication/
[RFC 4287]: http://tools.ietf.org/html/rfc4287
[RFC 3339]: http://www.faqs.org/rfcs/rfc3339.html
