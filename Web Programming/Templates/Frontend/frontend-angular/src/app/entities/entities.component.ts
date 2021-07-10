import { Component, OnInit } from '@angular/core';
import {Entity} from "../shared/entity.model";
import {EntityService} from "../shared/entity.service";
import {Router} from "@angular/router";
import {HttpHeaders} from "@angular/common/http";

@Component({
  selector: 'app-entities',
  templateUrl: './entities.component.html',
  styleUrls: ['./entities.component.css']
})
export class EntitiesComponent implements OnInit {
  entities!: Entity[];
  currentEntity!: Entity;

  pagination = false;
  start!: number;
  end!: number;
  rowsOnPage = 5

  constructor(private entityService: EntityService, private router: Router) { }

  ngOnInit(): void {
    // sessionStorage.setItem("authenticationType", "none");
    // sessionStorage.setItem("authenticationType", "simple");
    sessionStorage.setItem("authenticationType", "full");

    if (sessionStorage.getItem("authenticationType") === "none") {
      sessionStorage.setItem("authenticated", "true");
    } else {
      if (sessionStorage.getItem("authenticated") !== "true") {
        sessionStorage.setItem("authenticated", "false");
      }
    }

    this.entityService.getAll()
      .subscribe(entities => {
        this.entities = entities;
        if (this.pagination) {
          this.start = 0;
          this.end = this.start + this.rowsOnPage - 1;
        } else {
          this.start = 0;
          this.end = this.entities.length;
        }
      });
  }

  getAuthenticated() {
    return sessionStorage.getItem("authenticated");
  }

  getAuthenticationType() {
    return sessionStorage.getItem("authenticationType");
  }

  simpleAuthentication(username: string) {
    sessionStorage.setItem("username", username);
  }

  fullAuthentication(username: string, password: string) {
    const entity: Entity = <Entity>{username: username, password: password};
    this.entityService.authenticate(entity).subscribe(result => {
      console.log(result);
      sessionStorage.setItem("username", username);
      sessionStorage.setItem("authenticated", "true");
      window.location.reload();
    });
  }

  fullRegistration(username: string, password: string) {
    const entity: Entity = <Entity>{username: username, password: password};
    this.entityService.register(entity).subscribe(result => {
      console.log(result);
      sessionStorage.setItem("username", username);
      sessionStorage.setItem("authenticated", "true");
      window.location.reload();
    });
  }

  increment() {
    if (!(this.start + this.rowsOnPage >= this.entities.length)) {
      this.start = this.start + this.rowsOnPage;
      this.end = this.end + this.rowsOnPage;
    }
  }

  decrement() {
    if (!(this.end < this.rowsOnPage)) {
      this.start = this.start - this.rowsOnPage;
      this.end = this.end - this.rowsOnPage;
    }
  }

  rowClick(entity: Entity) {
    this.currentEntity = entity;
  }

  addEntity(title: string, genre: string) {
    const entity: Entity = <Entity>{title: title, genre: genre};
    this.entityService.save(entity).subscribe(result => {
      console.log(result);
      window.location.reload();
    });
  }

  deleteEntity(id: number) {
    const entity: Entity = <Entity>{id: id};
    this.entityService.delete(entity).subscribe(result => {
      console.log(result);
      window.location.reload();
    });
  }

  updateEntity(id: number, title: string, genre: string) {
    const entity: Entity = <Entity>{id: id, title: title, genre: genre};
    this.entityService.update(entity).subscribe(result => {
      console.log(result);
      window.location.reload();
    });
  }

  Number(value: string) {
    return Number(value);
  }
}
