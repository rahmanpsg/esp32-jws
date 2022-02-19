const char webpage[] PROGMEM =
    R"=====(
    <!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <meta http-equiv=”refresh” content=”5" />
    <title>Jadwal Waktu Sholat</title>
    <link
      rel="stylesheet"
      href="https://cdn.jsdelivr.net/npm/bulma@0.9.3/css/bulma.min.css"
    />
  </head>

  <body>
    <div id="app" class="container is-fluid">
      <section class="section">
        <div class="container">
          <h1 class="title">Jadwal Waktu Sholat</h1>
          <p class="subtitle">ESP32 Panel P10</p>
        </div>
      </section>

      <div class="columns is-mobile is-multiline">
        <div class="column is-full">
          <div class="card">
            <header class="card-header">
              <p class="card-header-title">
                <span class="icon is-large has-text-info">
                  <ion-icon name="person-circle" size="large"></ion-icon>
                </span>
                Profil
              </p>
            </header>
            <div class="card-content">
              <div class="content">
                <div class="columns is-mobile" v-for="profile in listProfile">
                  <div
                    class="column is-one-fifth-desktop is-one-third-mobile"
                    v-text="profile.title"
                  ></div>
                  <div class="column is-1" v-text="`:`"></div>
                  <div class="column" v-text="profile.text"></div>
                </div>
              </div>
            </div>
          </div>
        </div>

       

        <div class="column is-full">
          <div class="card">
            <header class="card-header">
              <p class="card-header-title">
                <span class="icon is-large has-text-info">
                  <ion-icon name="location" size="large"></ion-icon>
                </span>
                Pengaturan Lokasi
              </p>
              <div class="card-header-icon">
                <button class="button is-info" @click="postLokasi">
                  <span class="icon">
                    <ion-icon name="save"></ion-icon>
                  </span>
                </button>
              </div>
            </header>
            <div class="card-content">
              <div class="content">
                <div class="columns">
                  <div class="column">
                    <input
                      v-model="latitude"
                      class="input"
                      type="number"
                      placeholder="Latitude"
                    />
                  </div>
                  <div class="column">
                    <input
                      v-model="longitude"
                      class="input"
                      type="number"
                      placeholder="Longitude"
                    />
                  </div>
                  <div class="column">
                    <input
                      v-model="zonaWaktu"
                      class="input"
                      type="number"
                      placeholder="Zona Waktu"
                    />
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>

        <div class="column is-full">
          <div class="card">
            <header class="card-header">
              <p class="card-header-title">
                <span class="icon is-large has-text-info">
                  <ion-icon name="information-circle" size="large"></ion-icon>
                </span>
                Pengaturan Informasi
              </p>
              <div class="card-header-icon">
                <button class="button is-info" @click="postListInformasi">
                  <span class="icon">
                    <ion-icon name="save"></ion-icon>
                  </span>
                </button>
              </div>
            </header>
            <div class="card-content">
              <div class="content">
                <div v-for="(_, i) in listInformasi" class="columns is-mobile">
                  <div class="column is-10">
                    <input
                      v-model="listInformasi[i]"
                      class="input"
                      type="text"
                      placeholder="Pesan Informasi"
                    />
                  </div>
                  <div class="column is-2">
                    <button
                      v-if="i == listInformasi.length -1"
                      class="button"
                      @click="tambahInformasi"
                    >
                      <span class="icon">
                        <ion-icon name="add"></ion-icon>
                      </span>
                    </button>
                    <button v-else class="button" @click="hapusInformasi(i)">
                      <span class="icon">
                        <ion-icon name="close"></ion-icon>
                      </span>
                    </button>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>

      <div class="modal">
        <div class="modal-background"></div>
        <div class="modal-card">
          <header class="modal-card-head">
            <p class="modal-card-title">Informasi</p>
          </header>
          <section class="modal-card-body">
            <div
              class="notification"
              :class="[response.error ? `is-danger`: `is-info`]"
              v-text="response.message"
            ></div>
          </section>
        </div>
      </div>
    </div>

    <script src="https://unpkg.com/vue@next"></script>
    <script
      type="module"
      src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.esm.js"
    ></script>
    <script
      nomodule
      src="https://unpkg.com/ionicons@5.5.2/dist/ionicons/ionicons.js"
    ></script>
  </body>
  <script setup>
    const { ref, createApp, onMounted } = Vue;
    createApp({
      setup() {
        const loading = ref(true);
        const tanggal = ref(null);
        const jam = ref(null);
        const latitude = ref(null);
        const longitude = ref(null);
        const zonaWaktu = ref(null);
        const listInformasi = ref([]);
        const response = ref({
          error: false,
          message: null,
        });

        
        const url = new URL(document.URL);

        const listProfile = ref([
          {
            title: "Nama",
            text: "Muhammad Fadhil Arham",
          },
          {
            title: "Nim",
            text: "217280175",
          },
          {
            title: "Judul",
            text: "Sistem Pengendali Running Text P10 Berbasis Android",
          },
          {
            title: "Pembimbing 1",
            text: "Ade Hastuty, ST.,S.kom.,M.Kom",
          },
          {
            title: "Pembimbing 2",
            text: "Hj. Andi Irmayani P, ST.,MT",
          },
          {
            title: "Penguji 1",
            text: "Ir. Untung Suwardoyo, S.kom.,M.Kom",
          },
          {
            title: "Penguji 1",
            text: "Muh. Zainal, ST.,MT",
          },
        ]);

        function openModal() {
          const modal = document.querySelector(".modal");
          modal.classList.add("is-active");

          setTimeout(() => modal.classList.remove("is-active"), 2000);
        }

        const postWaktu = async () => {
          console.log(tanggal.value);
          console.log(jam.value);
          // const formData = new FormData();
          // formData.append("tanggal", tanggal.value);
          // formData.append("jam", jam.value);
          // const post = await fetch(`${url.href}waktu`, {
          //   method: "POST",
          //   body: formData,
          // });
          // const res = await post.json();
          // response.value = res;
          // openModal();
        };

        const getLokasi = async () => {
          const get = await fetch(`${url.href}lokasi`);

          const res = await get.json();

          latitude.value = res.latitude;
          longitude.value = res.longitude;
          zonaWaktu.value = res.zonaWaktu;
        };

        const postLokasi = async () => {
          const formData = new FormData();
          formData.append("latitude", latitude.value);
          formData.append("longitude", longitude.value);
          formData.append("zonaWaktu", zonaWaktu.value);

          const post = await fetch(`${url.href}lokasi`, {
            method: "POST",
            body: formData,
          });

          const res = await post.json();

          response.value = res;

          openModal();
        };

        const getListInformasi = async () => {
          const get = await fetch(`${url.href}informasi`);

          const res = await get.json();

          listInformasi.value = res;
        };

        const postListInformasi = async () => {
          const formData = new FormData();
          formData.append("listInformasi", JSON.stringify(listInformasi.value));

          const post = await fetch(`${url.href}informasi`, {
            method: "POST",
            body: formData,
          });

          const res = await post.json();

          response.value = res;

          openModal();
        };

        onMounted(() => {
          getLokasi();
          getListInformasi();
        });

        const tambahInformasi = () => {
          listInformasi.value.push([""]);
        };

        const hapusInformasi = (index) => {
          listInformasi.value.splice(index, 1);
        };

        return {
          loading,
          tanggal,
          jam,
          latitude,
          longitude,
          zonaWaktu,
          listProfile,
          listInformasi,
          postWaktu,
          postLokasi,
          postListInformasi,
          tambahInformasi,
          hapusInformasi,
          response,
        };
      },
    }).mount("#app");
  </script>
</html>


)=====";