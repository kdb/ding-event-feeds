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

### Ding event ###

## A complete example ##

This is a complete example of a Ding event feed.

    <?xml version="1.0" encoding="utf-8"?>
    <feed xmlns="http://www.w3.org/2005/Atom"
          xmlns:dingevent="https://github.com/kdb/ding-event-feeds/blob/master/spec/index.md">

      <title>Example Feed</title>
      <link href="http://example.org/"/>
      <updated>2003-12-13T18:30:02Z</updated>
      <author>
        <name>Andeby Bibliotekerne</name>
      </author>
      <id>http://bibliotek.andeby.rap/feed/ding-event</id>

      <entry>
        <title>Anders And holder foredrag om gåpåmod</title>
        <link href="http://bibliotek.andeby.rap/node/1337"/>
        <link rel="alternate" href="http://andeby.rap/event/and-2011"/>
        <category scheme="audience" term="children">Børn</category>
        <category scheme="audience" term="adults">Voksne</category>
        <category scheme="keywords">familien and</category>
        <category scheme="tags">kendte</category>
        <category scheme="tags">stædighed</category>
        <id>http://bibliotek.andeby.rap/node/1337</id>
        <published>2011-12-13T09:17:51+01:00</published>
        <updated>2011-12-13T18:30:02+01:00</updated>
        <author>Yvette Gåsefjer</author>
        <summary>Andebys mest stædige person kommer og fortæller om hans motivation</summary>
        <content type="html">
          &lt;p&gt;Brødtekst/indhold ligger her&lt;/p&gt;
        </content>
        <dingevent:image title="Anders i portræt">http://bibliotek.andeby.rap/files/images/and.png</ding:image>
        <dingevent:image title="Anders m. familie">http://bibliotek.andeby.rap/files/images/and2.png</ding:image>
        <dingevent:startdate>2012-03-26T15:30:00+01:00</dingevent:startdate>
        <dingevent:enddate>2012-03-26T18:00:00+01:00</dingevent:startdate>
        <dingevent:ticketlink>http://biletto.rap/ticket/22</dingevent:ticketlink>
        <dingevent:address>
          <dingevent:country>Amerika</dingevent:country>
          <dingevent:administrative_area>Andoming</dingevent:administrative_area>
          <dingevent:locality>Andeby</dingevent:locality>
          <dingevent:postal_code>1194</dingevent:postal_code>
          <dingevent:thoroughfare>Herrepærevej</dingevent:thoroughfare>
          <dingevent:premise>24</dingevent:premise>
          <dingevent:organisation_name>Herrepærevej Bibliotek</dingevent:organisation_name>
        </dingevent:address>
        <dingevent:email>herrep@bibliotek.andeby.rap</dingevent:email>
        <dingevent:phone>+899 24 24 24 24</dingevent:phone>
        <dingevent:price currency="DKK">53</dingevent:price>
      </entry>

    </feed>


[atom-sf]: http://www.atomenabled.org/developers/syndication/
[RFC 4287]: http://tools.ietf.org/html/rfc4287
[RFC 3339]: http://www.faqs.org/rfcs/rfc3339.html
