using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using ConsoleApp1.Models;

namespace ConsoleApp1.Data
{
    class MovieData
    {
        /*
        //private MovieContext mContext=new MovieContext();
        private MovieContext mContext;
        //public MovieData(MovieContext mContext)
        //{
        // this.mContext = mContext;
        // }

        public IEnumerable<Movie> GetAll()
        {
            return mContext.Movie;
        }
        public Movie Get(int id)
        {
            return mContext.Movie.Find(id);
        }

        public void Create(Movie item)
        {
            mContext.Movie.Add(item);
        }

        public void Update(Movie item)
        {
            //mContext.Entry(item).State = EntityState.Modified;
            mContext.Movie.Update(item);
        }

        public void Delete(int id)
        {
            Movie item = mContext.Movie.Find(id);
            if (item != null)
                mContext.Movie.Remove(item);
        }

        public void Save()
        {
            mContext.SaveChanges();
        }

        private bool disposed = false;

        public virtual void Dispose(bool disposing)
        {
            if (!this.disposed)
            {
                if (disposing)
                {
                    mContext.Dispose();
                }
            }
            this.disposed = true;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        */
    }

}