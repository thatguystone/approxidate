===========
approxidate
===========

approxidate is a quick way to get a unix timestamp from a ton of arbitrary date
formats. It consists of one function:

.. code-block:: python

    DateType = typing.Union[
        datetime.date,
        datetime.datetime,
        datetime.time,
        float,
        None,
    ]

    def approx(date: str, *, relative_to: DateType = None) -> float:
        """
        Get a unix timestamp from an arbitrary date string.

        If `relative_to` is None, and the given date string is missing date or time,
        now will be used. Otherwise, the missing units will be filled in from the
        date/time represented by relative_to.

        If `relative_to` is a float, it's treated as a unix timestamp.
        """

Example usage:

.. code-block:: python

    import datetime

    import approxidate

    approxidate.approx("10/10/2013 10:10:10.312 +0500")
    approxidate.approx("10/March/2013 10:10:10.312 +0500")
    approxidate.approx("10/Mar/2013 10:10:10.312 +0500")
    approxidate.approx("2013 march 10 04:00:07")
    approxidate.approx("2013 10 march 04:00:07")

    # Parsed relative to now
    approxidate.approx("00:00:07.657891")
    approxidate.approx("mar 10")
    approxidate.approx("10 mar 2013")
    approxidate.approx("march 10 2013")

    rel = datetime.datetime.now() + datetime.timedelta(hours=-1)
    approxidate.approx("00:00:07.657891", relative_to=rel)

    rel = datetime.date.today()
    approxidate.approx("00:00:07.657891", relative_to=rel)

    # Relative to a unix timestamp
    approxidate.approx("mar 10", relative_to=1579733041)
