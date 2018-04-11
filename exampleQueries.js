const q1 = {
  aggs: {
    categories: {
      filter: {},
      aggs: {
        'type.raw': {
          filter: {},
          aggs: {
            'type.raw': {
              terms: {
                field: 'type.raw',
                size: 20
              }
            }
          }
        }
      }
    },
    metascore: {
      filter: {
        range: {
          metaScore: {
            gte: 0,
            lte: 100
          }
        }
      },
      aggs: {
        metascore: {
          histogram: {
            field: 'metaScore',
            interval: 5,
            min_doc_count: 0,
            extended_bounds: {
              min: 0,
              max: 100
            }
          }
        }
      }
    },
    imdbRating: {
      filter: {
        range: {
          imdbRating: {
            gte: 0,
            lte: 10
          }
        }
      },
      aggs: {
        imdbRating: {
          histogram: {
            field: 'imdbRating',
            interval: 1,
            min_doc_count: 0,
            extended_bounds: {
              min: 0,
              max: 10
            }
          }
        }
      }
    },
    'actors.raw6': {
      filter: {},
      aggs: {
        'actors.raw': {
          terms: {
            field: 'actors.raw',
            size: 10
          }
        },
        'actors.raw_count': {
          cardinality: {
            field: 'actors.raw'
          }
        }
      }
    },
    'writers.raw7': {
      filter: {},
      aggs: {
        'writers.raw': {
          terms: {
            field: 'writers.raw',
            size: 10
          }
        },
        'writers.raw_count': {
          cardinality: {
            field: 'writers.raw'
          }
        }
      }
    },
    'countries.raw8': {
      filter: {},
      aggs: {
        'countries.raw': {
          terms: {
            field: 'countries.raw',
            size: 10
          }
        },
        'countries.raw_count': {
          cardinality: {
            field: 'countries.raw'
          }
        }
      }
    },
    runtimeMinutes9: {
      filter: {},
      aggs: {
        runtimeMinutes: {
          range: {
            field: 'runtimeMinutes',
            ranges: [
              {
                key: 'All'
              },
              {
                key: 'up to 20',
                from: 0,
                to: 20
              },
              {
                key: '21 to 60',
                from: 21,
                to: 60
              },
              {
                key: '60 or more',
                from: 61,
                to: 1000
              }
            ]
          }
        }
      }
    }
  },
  size: 12,
  sort: [
    {
      _score: 'desc'
    }
  ],
  highlight: {
    fields: {
      title: {},
      plot: {}
    }
  },
  _source: ['plot', 'title', 'poster', 'imdbId', 'imdbRating', 'year']
};

const q2 = {
  post_filter: { term: { 'actors.raw': 'Naveen Andrews' } },
  aggs: {
    categories: {
      filter: { term: { 'actors.raw': 'Naveen Andrews' } },
      aggs: {
        'type.raw': { filter: {}, aggs: { 'type.raw': { terms: { field: 'type.raw', size: 20 } } } }
      }
    },
    metascore: {
      filter: {
        bool: {
          must: [
            { term: { 'actors.raw': 'Naveen Andrews' } },
            { range: { metaScore: { gte: 0, lte: 100 } } }
          ]
        }
      },
      aggs: {
        metascore: {
          histogram: {
            field: 'metaScore',
            interval: 5,
            min_doc_count: 0,
            extended_bounds: { min: 0, max: 100 }
          }
        }
      }
    },
    imdbRating: {
      filter: {
        bool: {
          must: [
            { term: { 'actors.raw': 'Naveen Andrews' } },
            { range: { imdbRating: { gte: 0, lte: 10 } } }
          ]
        }
      },
      aggs: {
        imdbRating: {
          histogram: {
            field: 'imdbRating',
            interval: 1,
            min_doc_count: 0,
            extended_bounds: { min: 0, max: 10 }
          }
        }
      }
    },
    'actors.raw6': {
      filter: {},
      aggs: {
        'actors.raw': { terms: { field: 'actors.raw', size: 10 } },
        'actors.raw_count': { cardinality: { field: 'actors.raw' } }
      }
    },
    'writers.raw7': {
      filter: { term: { 'actors.raw': 'Naveen Andrews' } },
      aggs: {
        'writers.raw': { terms: { field: 'writers.raw', size: 10 } },
        'writers.raw_count': { cardinality: { field: 'writers.raw' } }
      }
    },
    'countries.raw8': {
      filter: { term: { 'actors.raw': 'Naveen Andrews' } },
      aggs: {
        'countries.raw': { terms: { field: 'countries.raw', size: 10 } },
        'countries.raw_count': { cardinality: { field: 'countries.raw' } }
      }
    },
    runtimeMinutes9: {
      filter: { term: { 'actors.raw': 'Naveen Andrews' } },
      aggs: {
        runtimeMinutes: {
          range: {
            field: 'runtimeMinutes',
            ranges: [
              { key: 'All' },
              { key: 'up to 20', from: 0, to: 20 },
              { key: '21 to 60', from: 21, to: 60 },
              { key: '60 or more', from: 61, to: 1000 }
            ]
          }
        }
      }
    }
  },
  size: 12,
  sort: [{ _score: 'desc' }],
  highlight: { fields: { title: {}, plot: {} } },
  _source: ['plot', 'title', 'poster', 'imdbId', 'imdbRating', 'year']
};

const q3 = {
  post_filter: { term: { 'actors.raw': 'Naveen Andrews' } },
  aggs: {
    categories: {
      filter: { term: { 'actors.raw': 'Naveen Andrews' } },
      aggs: {
        'type.raw': { filter: {}, aggs: { 'type.raw': { terms: { field: 'type.raw', size: 20 } } } }
      }
    },
    metascore: {
      filter: {
        bool: {
          must: [
            { term: { 'actors.raw': 'Naveen Andrews' } },
            { range: { metaScore: { gte: 0, lte: 100 } } }
          ]
        }
      },
      aggs: {
        metascore: {
          histogram: {
            field: 'metaScore',
            interval: 5,
            min_doc_count: 0,
            extended_bounds: { min: 0, max: 100 }
          }
        }
      }
    },
    imdbRating: {
      filter: {
        bool: {
          must: [
            { term: { 'actors.raw': 'Naveen Andrews' } },
            { range: { imdbRating: { gte: 0, lte: 10 } } }
          ]
        }
      },
      aggs: {
        imdbRating: {
          histogram: {
            field: 'imdbRating',
            interval: 1,
            min_doc_count: 0,
            extended_bounds: { min: 0, max: 10 }
          }
        }
      }
    },
    'actors.raw6': {
      filter: {},
      aggs: {
        'actors.raw': { terms: { field: 'actors.raw', size: 10 } },
        'actors.raw_count': { cardinality: { field: 'actors.raw' } }
      }
    },
    'writers.raw7': {
      filter: { term: { 'actors.raw': 'Naveen Andrews' } },
      aggs: {
        'writers.raw': { terms: { field: 'writers.raw', size: 10 } },
        'writers.raw_count': { cardinality: { field: 'writers.raw' } }
      }
    },
    'countries.raw8': {
      filter: { term: { 'actors.raw': 'Naveen Andrews' } },
      aggs: {
        'countries.raw': { terms: { field: 'countries.raw', size: 10 } },
        'countries.raw_count': { cardinality: { field: 'countries.raw' } }
      }
    },
    runtimeMinutes9: {
      filter: { term: { 'actors.raw': 'Naveen Andrews' } },
      aggs: {
        runtimeMinutes: {
          range: {
            field: 'runtimeMinutes',
            ranges: [
              { key: 'All' },
              { key: 'up to 20', from: 0, to: 20 },
              { key: '21 to 60', from: 21, to: 60 },
              { key: '60 or more', from: 61, to: 1000 }
            ]
          }
        }
      }
    }
  },
  size: 12,
  sort: [{ _score: 'desc' }],
  highlight: { fields: { title: {}, plot: {} } },
  _source: ['plot', 'title', 'poster', 'imdbId', 'imdbRating', 'year']
};
