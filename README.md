# Find-a-Storm
Storm data, provided by the National Weather Service (NWS), contain a chronological listing, by state, of
hurricanes, tornadoes, thunderstorms, hail, floods, drought conditions, lightning, high winds, snow, temperature extremes and other weather phenomena. The data also contain statistics on personal injuries and
damage estimates. Data is available from 1950 to the present for the United States of America.
This project goal of this project is to implement a storm event application that manages storm event
data and uses it to answer queries meeting given selection criteria. <br>

The storm event data will be indexed by a __hash table__, and a __binary search tree__ and __max-heap__ as appropriate to support the queries.

## How to run the program
Use the following command line format for the respective queries: 
  * `find event <event id>` : searches the __hash table__ for the storm event with identifier event id. Example: find event 383097 // find storm event with given id
  * `find max <number> <YYYY> <damage type>` : where number is an integer ≤ 50, YYYY is either a specific four digit year or the literal all, and damage type is either damage property or damage crops. This query builds a max-heap on the field damage type for the given year YYYY or all years of storm data.
    It executes number Delete-Max operations on the heap, each time printing information for the most expensive storm in terms of the damage it caused to property or crops. Specifically, for each event
    print the event id, event type, and amount of damage of as a dollar amount, on a single line.
    Example: find max 4 1950 damage_property // find 4 most expensive storms to property in 1950
    `find max 10 all damage_crops` // find 10 most expensive storms to crops in all years


## The Storm and Fatality Event Data Format

  * There are two types of data files :
    * Year Storm details data (`details-YYYY.csv`)    
    * Fatalities data (`fatalities-YYYY.csv`)
    * Data columns in the details-YYYY.csv files: *The first line of the file contains the field names, and should be skipped*
      * `event id`: An identifier assigned by the NWS for a specific storm event; it links the storm event with the information in the fatalities-YYYY.csv file. Example: 383097.
      * `state`: The state name, spelled in all capital letters, where the event occurred. Example: GEORGIA.
      * `year`: The four digit year for the event in this record. Example: 2000.
      * `month name`: Name of the month for the event in this record spelled out. Example: January.
      * `event type`: The event types permitted are listed in Table 1, spelled out.
      * `cz type`: Indicates whether the event happened in a county/parish (C), zone (Z), or marine (M).
      * `cz name`: County/Parish, Zone or Marine name assigned to the county or zone. Example: AIKEN.
      * `injuries direct`: The number of injuries directly related to the weather event. Examples: 0, 56.
      * `injuries indirect`: The number of injuries indirectly related to the weather event. Examples: 0, 87.
      * `deaths direct`: The number of deaths directly related to the weather event. Examples: 0, 23.
      * `deaths indirect`: The number of deaths indirectly related to the weather event. Examples: 0, 4, 6.
      * `damage property`: The estimated amount of damage to property incurred by the weather event, e.g., 10.00K = $10,000; 10.00M = $10,000,000. Examples: 10.00K, 0.00K, 10.00M.
      * `damage crops`: The estimated amount of damage to crops incurred by the weather event e.g., 10.00K = $10,000; 10.00M = $10,000,000. Examples: 0.00K, 500.00K, 15.00M.
      * `tor f scale`: Enhanced Fujita Scale describes the strength of the tornado based on the amount and type of damage caused by the tornado. The F-scale of damage varies in the destruction area; therefore, the highest value of the F-scale is recorded for each event. Examples: EF0, EF1, EF2, EF3, EF4, EF5
     * Data columns in the fatalities-YYYY.csv files:
      * `fatality id`: An identifier assigned by NWS to denote the individual fatality that occurred within a storm event. Example: 17582.
      * `event id`: An identifier assigned by NWS to denote a specific storm event; it links the fatality with the storm event in the details-YYYY.csv file. Example: 383097.
      * `fatality type`: D represents a direct fatality, whereas I represents an indirect fatality. Example: D.
      * `fatality date`: Date and time of fatality in MM/DD/YYYY HH:MM:SS format, 24 hour time. Example: 04/03/2012 12:00:00.
      * `fatality age`: The age of the person suffering the fatality. Example: 38.
      * `fatality sex`: The gender of the person suffering the fatality. Example: F.
      * `fatality location`: The fatality locations permitted are listed in Table 2, spelled out. Example: Under Tree.

