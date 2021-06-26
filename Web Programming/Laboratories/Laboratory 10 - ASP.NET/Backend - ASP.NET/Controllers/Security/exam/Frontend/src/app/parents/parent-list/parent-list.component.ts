import { Component, OnInit } from '@angular/core';
import {Parent} from "../shared/parent.model";
import {ParentService} from "../shared/parent.service";
import {Router} from "@angular/router";
import {Movie} from "../shared/movie.model";
import {Document} from "../shared/document.model";

@Component({
  selector: 'app-parent-list',
  templateUrl: './parent-list.component.html',
  styleUrls: ['./parent-list.component.css']
})
export class ParentListComponent implements OnInit {
  parents!: Parent[];
  documents!: Document[];
  movies!: Movie[];
  document!: Document;

  constructor(private parentService: ParentService, private router: Router) {
    if (localStorage.getItem('username') == null) {
      router.navigateByUrl('/login');
    }
  }

  ngOnInit(): void {
    this.parentService.getAllMovies()
      .subscribe(movies => this.movies = movies);
    this.parentService.getAllDocuments()
      .subscribe(docs => {
        this.documents = docs
      });
  }

  delete(id: number) {

  }

  goToUpdate(id: number) {

  }

}
